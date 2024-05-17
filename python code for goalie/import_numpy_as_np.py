import numpy as np
import cv2
from matplotlib import pyplot as plt
import serial
import math
import time

# initialization
ser = serial.Serial('COM8', 9600, timeout=0.1)
ex = 0
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
cap = cv2.VideoCapture(0)

tp = 300
ty = 315
off = 'off'

# main loop
while cap.isOpened():
                ret, frame= cap.read()
                #cv2.imshow('webcam', frame)
                frame=cv2.flip(frame,1)
                gray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
                faces= face_cascade.detectMultiScale(gray,1.1,6)
                for (x, y, w, h) in faces:
                    cv2.circle(frame, (x + w // 2, y + h // 2), 2, (0, 255, 0), 2)
                    cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 165, 255), 2)
                    #cv2.rectangle(frame, (640 // 2 - 30, 480 // 2 - 30), (640 // 2 + 30, 480 // 2 + 30),
                                  #q(255, 255, 255), 3)

                    ty = x + math.floor(w / 2)
                    tp = y + math.floor((7 * h) / 20)

                # cv2.imshow('img', frame)

                # converting coordinates to pitch and yaw angles for servos
                sendy = str(math.floor(ty * (-45 / 573) + 117.9))
                sendp = str(math.floor(tp * (-45 / 470) + 75))
                #print('X' + sendy + 'Y' + sendp)
                #send = 'X' + sendy + 'Y' + sendp
                #print(send)

                #send = 'X{0}Y{1}'.format((sendy), (sendp))
                #print(send)

                # ensures that sendy is 3 bytes
                #if len(sendy) == 2:
                #    sendy = '0' + sendy
                #elif len(sendy) == 1:
                #    sendy = '00' + sendy
                #elif len(sendy) < 1 or len(sendy) > 3:
                #    sendy = '000'




                send = 'X{0}Y{1}'.format((sendy), (sendp))
                sendO = 'O{0}O{1}'.format((sendy), (sendp))
                #print(send)
                #print(sendO)
                #print(f"{faces}")
                #print(type(faces))
                if faces != ():
                    ser.write(send.encode('utf-8'))
                    time.sleep(.001)
                    print(send)


                else:
                    ser.write(off.encode('utf-8'))
                    print(off)

                cv2.imshow('img',frame)


                if cv2.waitKey(10)&0xFF== ord('q'):
                                break
cap.release()
cv2.destroyAllWindows()


