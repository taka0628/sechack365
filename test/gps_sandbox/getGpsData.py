from gps3 import gps3
import csv

gps_socket = gps3.GPSDSocket()
data_stream = gps3.DataStream()
gps_socket.connect()
gps_socket.watch()
limit = 100


print("データ数を入力してください\n>", end="")
while 1:
    temp = str(input())
    if str.isdecimal(temp) == True:
        if int(temp) >= 1:
            break

    print("もう一度入力してください\n>", end="")

limit = int(temp)

with open('gps.csv', 'w') as f:
    writer = csv.writer(f, lineterminator='\n')  # 改行コード（\n）を指定しておく

    i = 0
    for new_data in gps_socket:
        if new_data:
            data_stream.unpack(new_data)
            list = [data_stream.TPV['time'],
                    data_stream.TPV['lat'],
                    data_stream.TPV['lon'],
                    data_stream.TPV['alt'],
                    data_stream.TPV['speed']]
            if "n/a" in str(list[:2]):
                continue
            writer.writerow(list)     # list（1次元配列）の場合
            i += 1
            print("n: {}/{}\r".format(i, limit), end="")
            if i >= limit:
                break
