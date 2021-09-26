import os
import glob
import random

import cv2
import verovio
from cairosvg import svg2png
import numpy as np
from pgmagick import Image


# IMAGE PROCESSING WORKFLOW
# 1) Convert Humdrum **kern files to SVG files -> kerntosvg
# 2) Filter out those that do not meet end-to-end OMR condition (single-staff section or pair-staff section, as appropriate) -> getMultiStaff
# 3) Convert to PNG -> svg2png
# 4) Crop PNG files to reduce their size and the music information is centered -> crop_and_filter


def kerntosvg(kern_path: str, kern_folder: str, svg_folder: str, extensionKern: str):
    kernfiles = glob.glob(kern_path + '/*')
    tk = verovio.toolkit()
    for kernfile in kernfiles:
        svgfilename = kernfile.replace(kern_folder, svg_folder)
        svgfilename = svgfilename.split(extensionKern)[0] + '.svg'
        tk.loadFile(kernfile)
        tk.getPageCount()
        tk.renderToSVGFile(svgfilename, 1)
    return


def getMultiStaff(svg_path: str, mode: str):
    svgfiles = glob.glob(svg_path + '/*')
    deleted = []

    for svgfile in svgfiles:
        with open(svgfile, 'r') as file:
            data = file.read()
            times = data.count('clef')
        if mode == 'mono' or mode == 'homo' or mode == 'poly-ss':
            if times > 1:
                deleted.append(svgfile)
        elif mode == 'piano-mono' or mode == 'piano-homo':
            if times > 2:
                deleted.append(svgfile)

    return deleted


def svgtopng(svg_path: str, svg_folder: str, image_folder: str, extensionImage: str):
    svgfiles = glob.glob(svg_path + '/*')
    for svgfile in svgfiles:
        pngfile = svgfile.replace(svg_folder, image_folder)
        pngfile = pngfile.split('.svg')[0] + extensionImage
        with open(svgfile, mode="r") as input_file:
            svg_stream = input_file.read()
            # See https://github.com/Kozea/CairoSVG/issues/300 for the reason why we have to replace inherit with visible here
            svg_stream = svg_stream.replace("overflow=\"inherit\"", "overflow=\"visible\"")
            svg2png(bytestring=svg_stream, background_color="transparent", write_to=pngfile)
    return


def crop_and_filter(image_path: str, extensionImage: str):
    crop_path = os.path.join(image_path, 'CROPPED')
    os.makedirs(crop_path, exist_ok=True)

    pngfiles = glob.glob(image_path + '/*')
    for pngfile in pngfiles:
        if pngfile.endswith(extensionImage):
            image = cv2.imread(pngfile, cv2.IMREAD_UNCHANGED)
            image = np.array(image)[:, :, 3]  # Look only alpha channel

            _, image_th = cv2.threshold(image, 127, 255, 0)
            # cropped = cv2.erode(image, np.ones((1, 30), np.uint8), iterations=1)
            cropped = cv2.dilate(image, np.ones((100, 1), np.uint8), iterations=1)
            cropped = cv2.erode(cropped, np.ones((100, 1), np.uint8), iterations=1)

            contours, hierarchy = cv2.findContours(cropped, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

            # Find the index of the largest contour
            areas = [cv2.contourArea(c) for c in contours]
            max_index = np.argmax(areas)
            areas.sort(reverse=True)
            areas = np.array(areas)

            if np.sum(areas > 50000) == 1:
                cnt = contours[max_index]
                x, y, w, h = cv2.boundingRect(cnt)

                filename = pngfile.replace(image_path, crop_path)

                cv2.imwrite(filename,
                            (255. - image[max(0, y - 5):min(y + h + 5, image.shape[0]),
                                    max(0, x - 5):min(x + w + 5, image.shape[1])]))

    return crop_path


def distort(crop_path: str, extensionImage: str):
    # Distort PNG images to simulate imperfections introduced by taking pictures of sheet music in a real scenario
    # Distorter based on:
    # Calvo - Zaragoza, J.; Rizo, D.
    # Camera - PrIMuS: Neural end - to - end Optical Music Recognition on realistic monophonic scores.
    # In Proceedings of the 19th International Society for Music Information Retrieval Conference, Paris.2018, pp.248-255
    dist_path = os.path.join(crop_path, 'DISTORTED')
    os.makedirs(dist_path, exist_ok=True)

    cropfiles = glob.glob(crop_path + '/*')
    for cropfile in cropfiles:
        if cropfile.endswith(extensionImage):
            im = Image(cropfile)
            im.implode(round(random.uniform(0.00, 0.07), 2))
            # TODO See how to use im.chop
            #im.chop(int(random.randint(1, 5)), int(random.randint(1, 6)), int(random.randint(1, 300)), int(random.randint(1, 50)))
            im.swirl(round(random.uniform(-3.00, 3.00), 2))
            im.spread(2)
            im.shear(round(random.uniform(-5.00, 5.00), 2), round(random.uniform(-1.50, 1.50), 2))
            im.shade(round(random.uniform(0.00, 120.00), 2), round(random.uniform(80.00, 110.00), 2))
            im.wave(round(random.uniform(0.00, 0.50), 2), round(random.uniform(0.00, 0.40), 2))
            im.rotate(round(random.uniform(0.00, 0.30), 2))
            # TODO See how to use im.addNoise
            # im.addNoise(round(random.uniform(0.00, 1.20), 2))
            im.wave(round(random.uniform(0.00, 0.50), 2), round(random.uniform(0.00, 0.40), 2))
            im.motionBlur(round(random.uniform(-7.00, 5.00), 2), round(random.uniform(-7.00, 7.00), 2), round(random.uniform(-7.00, 6.00), 2))
            im.medianFilter(round(random.uniform(0.00, 1.10), 2))

            filename = cropfile.replace(crop_path, dist_path)
            im.write(filename)

    return

