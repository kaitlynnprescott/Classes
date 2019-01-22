import random
import math
import operator
from PIL import Image

def dist(a, b):
    return math.sqrt((a[0] - b[0])**2 + (a[1] - b[1])**2)

def islinler(pt1, pt2, c):
    ac = dist(a,c)
    cb = dist(c,b)
    ab = dist(a,b)
    x = ac + cb <= 1.001 * ab
    y = ac + cb >= ab
    return x and y

def ransac(features, numit):
    inlier_dict = {}
    length = len(features)
    for i = range(numit):
        sample1 = features[random.randint(0, length-1)]
        sample2 = features[random.randint(0, length-1)]
        inliers = 0
        for pt in features:
            if pt not in [sample1, sample2]:
                if (isinlier(sample1, sample2, pt)):
                    features.remove(pt)
                    inliers += 1
        inlier_dict[(sample1, sample2)] = inliers

    inliers_sorted = dict(sorted(inliers.items(), key = operator.itemgetter(1), reverse = True)[:4])
    return inliers_sorted
                    
