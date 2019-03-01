'''
This code uses Friis equation to find the transmission distance
'''

from math import sqrt, pi


def line_of_sight(d, h1=0, h2=0):
    '''
    Function for solving the line of sight for 2 modules
    :param d: distance between modules
    :param h1: the height of the transmitter
    :param h2: the height of the receiver
    :return: True - modules in line of sight, False - no
    '''

    earth_r = 6365000
    LOS = (sqrt(2*h1*earth_r) + sqrt(2*h2*earth_r)) / 1000
    if d < LOS:
        return True
    else:
        return False


def friis_eq(pt, pr, lb, gt=1, gr=1):
    '''
    Uses Friis eequation to find the max distance between modules, which connected to the desired speed
    :param pt: transmitter power
    :param pr: receiver sensitivity for desired speed
    :param gt: transmitter antenna gain
    :param gr: receiver antenna gain
    :param lb: wavelenght
    :return: max distance
    '''

    max_dist = sqrt((pt*gt*gr*lb**2) / (pr*16*pi**2))
    return max_dist


def dbm_to_mw(dbm):
    '''
    Translate dBm to mW
    :param dbm: power in dBm
    :return: power in mW
    '''

    mw = 10**(0.1*dbm)
    print(dbm, mw)
    return mw


if __name__ == "__main__":
    pt = 13
    pr = -87    # receiver power in dbm for 
    lb = 0.692  # wavelenght for frequency 433 MGh
    print(friis_eq(dbm_to_mw(pt), dbm_to_mw(pr), lb))

    help(friis_eq)

