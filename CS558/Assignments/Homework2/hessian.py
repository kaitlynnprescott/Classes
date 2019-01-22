import math


def hessian(im, sigma, threshold, sz):
    im = getImMatrix(im)
    hi = len(im[0])
    wi = len(im)
    gaussfilt = gauss_kernel(sigma)
    G = filt(gaussfilt, im)
    Gx = filt(SOBEL_X, G)
    Gy = filt(SOBEL_Y, G)
    Gxx = filt(SOBEL_X, Gx)
    Gxy = filt(SOBEL_Y, Gx)
    Gyy = filt(SOBEL_Y, Gy)

    determinant = Gxx * Gyy - (Gxy**2)
    wd = len(determinant[0])
    hd = len(determinant)

    for i in range(wd):
        for j in range(hd):
            if determinant[i][j] < threshold:
                determinant[i][j] = 0

    newim = [ [[0] * wi] * hi]
    for i in range(hi):
        for j in range(wi):
            if determinant[i][j] >= localmax(i,j,determinant,sz) and determinant[i][j]!=0:
                newim[i][j] = 1

    features = []
    for i in range(wd):
        for j in range(hd):
            if newim[i][j] != 0:
                point = (i,j)
                features += point
    return features, newim

def localmax(x, y, im, sz):
    szlen = int(sz/2)
    im = getImMatrix(im)
    hi = len(im[0])
    wi = len(im)
    minx = x-szlen
    if minx < 0:
        minx = 0
    maxx = x+szlen+1
    if maxx > wi:
        maxx = wi-1
    miny = y-szlen
    if miny < 0:
        miny = 0
    maxy = y+szlen+1
    if maxy < hi:
        maxy = hi-1
    maxval = im[x][y]
    for i in range(minx+1, maxx):
        for j in range(miny+1, maxy):
            maxval = max(im[i][j], maxval)
    return maxval
