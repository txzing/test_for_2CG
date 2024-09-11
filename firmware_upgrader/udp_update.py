import struct
import hashlib
from socket import *
import time
from PyQt5 import QtCore#, QtGui
from PyQt5.QtWidgets import *


class UDP_sent_thread(QtCore.QThread):
    finishSignal = QtCore.pyqtSignal(list)
    def __init__(self,uploadFileName, server_ip,port,parent=None):
        super(UDP_sent_thread, self).__init__(parent)
        self.uploadFileName = uploadFileName
        self.server_ip = server_ip
        self.server_port = int(port)
        self.thread_stop = False

    def run(self):
        buf = 1024
        read_len = 0
        s = socket(AF_INET,SOCK_DGRAM)            # Create a socket object
        host = (self.server_ip,self.server_port)
        file_name = self.uploadFileName
       
        f=open(file_name,"rb")
        fcont = f.read()
        totoal_len = f.tell()
        fmd5 = hashlib.md5(fcont)
        fmd5_bytes=bytes.fromhex(fmd5.hexdigest().upper())
        md5string = fmd5.hexdigest().upper()
        fileLen_byts=totoal_len.to_bytes(4,'little')
        file_len_str = str(totoal_len)
        print(file_len_str)
        print(md5string)
        print(totoal_len)
        f.close()

        self.finishSignal.emit([self.uploadFileName, " md5sum:", md5string, " \n"])  ## 发送信号 告诉主线程
        sendDataFirst = struct.pack('!6s%ds%ds' % (len(fmd5_bytes), len(fileLen_byts)), 'md5sum'.encode(), fmd5_bytes, fileLen_byts)
        s.sendto(sendDataFirst, host)

        s.sendto(b"clear",host)

        # 第一次接收数据
        responseData = s.recvfrom(1024)
        recvData, serverInfo = responseData
        print("recv ack")
         # 解包
        if recvData.decode() != "Clear received data\r\n":
            print("服务器发生错误！")
            f.close()
            s.close()
            return
        print("start recv")
        f=open(file_name,"rb")
        send_len  = 0
        pre_percent = 0
        while not self.thread_stop:
            # 　从文件中读取1024字节数据
            readFileData = f.read(1024)
            read_len = len(readFileData)
            send_len += read_len
            # print(send_len)
            if pre_percent == 0 and send_len == 1024:
                self.finishSignal.emit(["Transmission Start!!!"]) 
                self.finishSignal.emit(["Transmission progress: 0%"]) 
            # 　打包
           
            s.sendto(readFileData, host)
            time.sleep(0.00015)
            data = [0,10,20,30,40,50,60,70,80,90,100]
            process_percent = int((send_len /totoal_len) *100)
            if pre_percent != process_percent:
                pre_percent = process_percent
                if process_percent in data:
                    self.finishSignal.emit(["Transmission progress: " + str(process_percent) + "%"]) 

            if len(readFileData) < 1024:
                print("%s文件上传成功！" % self.uploadFileName)
                f.close()
                self.thread_stop = True
                self.finishSignal.emit(["transfer success !", "wait for flash erase...."])
                time.sleep(0.1)
                s.sendto(b"update", host)
                break
        while True:
            recvData, serverInfo = s.recvfrom(128)
            realstr = bytes.decode(recvData)
            time.sleep(0.001)
            self.finishSignal.emit([realstr])
            if realstr == "Verify Operation Successful.\r\n":
                s.close()
                break
            elif realstr == "md5sum Verify Failed!!!\r\n":
                s.close()
                break
            elif realstr == "Verify data error at address 0x%lx.\r\n":
                s.close()
                break
        s.close()
       

    def stop(self):
        self.thread_stop = True
