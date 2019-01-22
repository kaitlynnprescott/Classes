import math
import operator

def get_paramaters(p1, p2):
    x1 = p1[0]
    x2 = p2[0]
    y1 = p1[1]
    y2 = p2[1]
    if (x1 != y1):
        m  = (y2 - y1)/(x2 - x1)
        b = int(y1 - (m * x1))
        return (m,b)
    return None

def hough(features):
    points = {}
    length = len(features)
    for i in range(100000):
        samp1 = features[random.randint(1, length-1)]
        samp2 = features[random.randint(1, length-1)]
        paramaters = get_parameters(samp1, samp2)
        if paramaters is None:
            continue
        if parameters not in points.keys():
            points[parameters] = 1
        else:
            points[parameters] += 1
    sorted_points = sorted(points.items(), key = operator.itemgetter(1), reverse = True)
    four = dict(sorted_points[:4])
    lines = []
    for pt in four:
        y_int = (0,point[1])
        scndpt = (5000, point[0]*5000+point[1])
        endpoints = (y_int, scndpt)
        lines.append(endpoints)
    return lines

