# -*- coding: utf-8 -*-


import decimal
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
from numpy.core.defchararray import center, count
from numpy.core.function_base import linspace
from numpy.lib.function_base import average, median
from numpy.lib.scimath import sqrt
import pandas as pd
import numpy as np
import csv
from decimal import Decimal as dm
import math
from sklearn.preprocessing import MinMaxScaler


from numpy.core.fromnumeric import var

cd = [35.097677777777776, 136.0307388888889]

gpsData = None

csvFile = open('gps.csv', 'r')
gpsData = list(csv.reader(csvFile, lineterminator='\n'))


def printScatter(x: list, y: list, xlabel="", ylabel=""):
    fig = plt.figure()
    ax = fig.add_subplot(111)
    plt.gca().get_xaxis().get_major_formatter().set_useOffset(False)
    plt.gca().get_xaxis().get_major_formatter().set_useOffset(False)
    plt.gca().get_yaxis().set_major_locator(ticker.MaxNLocator(integer=True))
    plt.gca().get_yaxis().set_major_locator(ticker.MaxNLocator(integer=True))

    ax.set_xlabel("latitude", size=14, weight="light")
    ax.set_ylabel("longitude", size=14, weight="light")
    tempX = x
    tempX.append(cd[0])
    tempY = y
    tempY.append(cd[1])
    ax.set_xticks([min(tempX), average(tempX), max(tempX)])
    ax.set_yticks([min(tempY), average(tempY), max(tempY)])
    ax.scatter(x, y)
    ax.scatter(cd[0], cd[1], color='olive')
    plt.grid(True)
    plt.show()


def printBar(x: list):
    val = [0] * 10
    x = np.abs(x)
    limt = int(max(x))
    for hoge, data in enumerate(x):
        if int(data/(limt / 10)) >= len(val):
            val[-1] += 1
            continue

        val[int(data/(limt / 10))] += 1

    xbar = linspace(0, limt, 10)
    plt.xlabel("diff")
    plt.ylabel("cnt")
    plt.bar(xbar, val)
    plt.show()


def cal_distance(point1, point2):

    equator_radius = 6378137.0                    # 赤道半径
    pole_radius = 6356752.314245                  # 極半径
    # 緯度経度をラジアンに変換
    lat_kamata = math.radians(point1[0])
    lon_kamata = math.radians(point1[1])
    lat_yokosukachuo = math.radians(point2[0])
    lon_yokosukachuo = math.radians(point2[1])

    lat_difference = lat_kamata - lat_yokosukachuo       # 緯度差
    lon_difference = lon_kamata - lon_yokosukachuo       # 経度差
    lat_average = (lat_kamata + lat_yokosukachuo) / 2    # 平均緯度

    e2 = (math.pow(equator_radius, 2) - math.pow(pole_radius, 2)) \
        / math.pow(equator_radius, 2)  # 第一離心率^2

    w = math.sqrt(1 - e2 * math.pow(math.sin(lat_average), 2))

    m = equator_radius * (1 - e2) / math.pow(w, 3)  # 子午線曲率半径

    n = equator_radius / w                         # 卯酉線曲半径

    distance = math.sqrt(math.pow(m * lat_difference, 2)
                         + math.pow(n * lon_difference * math.cos(lat_average), 2))  # 距離計測

    return distance


def analyse(x: list):
    print("[n]: {}\n[平均]: {}\n[分散]: {}\n[min, max]: {}, {}".format(
        len(x), np.average(x), np.var(x), np.min(x), np.max(x)))


def linear(x, y):
    min_max_li = np.array([[min(x), min(y)], [max(x), max(y)]])  # shape=(2, 2)
    mmscaler = MinMaxScaler(feature_range=(0, 1), copy=True)
    mmscaler.fit(min_max_li.astype('float'))
    mmscaler = MinMaxScaler(feature_range=(0, 1), copy=True)
    mmscaler.fit(min_max_li.astype('float'))
    scaled_sample = mmscaler.transform(np.transpose([x, y]))
    print(scaled_sample)


x = []
y = []
for i, data in enumerate(gpsData):
    x.append(float(data[1]))
    y.append(float(data[2]))

distance = []
for i in range(len(x)):
    distance.append(cal_distance([x[i], y[i]], cd))

analyse(distance)
printBar(distance)
printScatter(x, y)

averageGPS = []
for i in range(len(x)):
    averageGPS.append(cal_distance([x[i], y[i]], [average(x), average(y)]))

printBar(averageGPS)
