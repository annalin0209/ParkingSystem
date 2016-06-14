from __future__ import print_function
import argparse
import binascii
import time
import os
import sys
import btle
import struct
import threading
import time
import json,httplib,urllib
import time

###Parse Parameter
APPLICATION_ID = 'U3YH75bKsO1mEapjIMvplgEZoqg1CQ08H0yL2tNH'
REST_API_KEY = 'xMZO1uIm8IWHi3kcoOVlRgnQBM5gtcSmAG8XDVbd'

connection = httplib.HTTPSConnection('api.parse.com', 443)
connection.connect()

### global parameters
numOfDongle = 5
iface = 1
count = 0
 
CharteristicUUID = 'fff0'

reminder_list = []
conn_list = []

lock = threading.Lock()

def checkDataExist(dataType,value):

   # print ("dataType %s ,value %s" % (dataType,value))
       ### search data (set paramter)
    params = urllib.urlencode({"where":json.dumps({
       dataType: value
     })})
    ### search of request
    connection.request('GET', '/1/classes/parkingSpace?%s' % params, '', {
       "X-Parse-Application-Id": APPLICATION_ID,
       "X-Parse-REST-API-Key": REST_API_KEY
     })
    ### result from DB  and Decode
    result = json.loads(connection.getresponse().read())
    if not result['results'] :
        print("No data on DB , please creat this data on DB")
        return False
    else:
        print ("The data has existed %s" % result['results'][0]['objectId'])
        return result['results'][0]['objectId']

def uploadData(value): ###first upload data

    connection.request('POST', '/1/classes/parkingSpace', json.dumps({
       "empty": True ,
       "macAddress": value
     }), {
       "X-Parse-Application-Id": APPLICATION_ID,
       "X-Parse-REST-API-Key": REST_API_KEY,
       "Content-Type": "application/json"
     })
    results = json.loads(connection.getresponse().read())
    print(results)

def updateData(macAddress , value):


    ###chcek Data on DB and get hashKey
    HashKey = checkDataExist("macAddress",macAddress)
    print(HashKey) 
  
    if not HashKey:
        uploadData(macAddress)  
    ### upadte the data
    if value == '01':
        connection.request('PUT', '/1/classes/parkingSpace/%s' %HashKey, json.dumps({
            "empty" : True ,
            "endTime": time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()) 

             }), {
            "X-Parse-Application-Id": APPLICATION_ID,
            "X-Parse-REST-API-Key": REST_API_KEY,
            "Content-Type": "application/json"
        })
    else:
        connection.request('PUT', '/1/classes/parkingSpace/%s' %HashKey, json.dumps({
            "empty" : False ,
            "startTime": time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()) 
             }), {
            "X-Parse-Application-Id": APPLICATION_ID,
            "X-Parse-REST-API-Key": REST_API_KEY,
            "Content-Type": "application/json"
        })



    result = json.loads(connection.getresponse().read())
    print(result)


def scanThread():

    print("hello BLE scanner")
    scanner = btle.Scanner()

    global count
    global iface

    while True:
        print("still scanning... count:" , len(conn_list))
        with lock:
            devcies = scanner.scan(timeout = 5)

        reminder_list = []

        for dev in devcies:
            for (sdid , desc , val) in dev.getScanData():  
              #  print("Devcies %s ,%s , UUID = %s " %(dev.addr ,desc , val))
                if val == CharteristicUUID:
               #     print("devcies %s ,descriptor: %s , UUID = %s " %(dev.addr ,desc , val))
                    reminder_list.append(dev)


        for dev in reminder_list:
            with lock:
                try:
                    conn = btle.Peripheral(dev.addr , dev.addrType , iface = iface)
                    conn.setDelegate(btle.DefaultDelegate())
                    count += 1
                    if iface == numOfDongle:
                        iface = 1
                    else:
                        iface += 1 
                #   print("test connection successfully")
                except:
                    print("connection failed")

            try:
                # 0000fed0-0000-1000-8000-00805f9b34fb
                service = conn.getServiceByUUID("0000fff6-0000-1000-8000-00805f9b34fb")
                char = service.getCharacteristics("0000fffb-0000-1000-8000-00805f9b34fb")[0] 
                conn.writeCharacteristic(char.handle+2,struct.pack('<bb', 0x01, 0x00), True)
                conn_list.append(conn)
                #check if the node exist on DB , if not creat on DB
            except:
                try:
                    conn_list.remove(dev)
                except:
                    lulala = 0
                print("Set notification failed , Remove the device from conn_list")

            try:
                objectId = checkDataExist("macAddress",dev.addr)
                if objectId == False:
                    uploadData(dev.addr)
            except:
                print ("CheckDataExist failed")
              



def main():

    print("hello BLE Centrals")

    global count
    global iface
    
    test = 0
    while True:
        for dev in conn_list:
           # try:
            if dev.waitForNotifications(0.01):
                print("iface %d , devcies %s : %s" %(dev.iface , dev.deviceAddr , dev.gyrodata))
                updateData(dev.deviceAddr,dev.gyrodata)
           # except:
            #    conn_list.remove(dev)
            #    print("Disconnect ! Remove the device from list")


if __name__ == '__main__':
    th =  threading.Thread(target = scanThread)
    th.start()

    main()
