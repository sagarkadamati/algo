# importing libraries
import cv2
import time
import datetime
import os
import sys
import math
import ntpath
import numpy as np
# import playsound

video1_file = sys.argv[1]
try:
	video2_file = sys.argv[2]
except:
	video2_file = ""
try:
	out_file = sys.argv[3]
except IndexError:
	out_file = ntpath.basename(video1_file)

# playsound.playsound('video2.mp3', True)

run = True
speed = 33
collect_start = False
collect_end = False

# Create a VideoCapture object and read from input file
cap = cv2.VideoCapture(video1_file)
if (cap.isOpened() == True):
	video1_fps    = cap.get(cv2.CAP_PROP_FPS)
	video1_start  = "00:00:00.000"
	video1_end    = "00:00:00.000"
	video1_skip   = True
	video1_skip_frames = 0

	# Display the resulting frames for video1
	cv2.namedWindow("Video1", cv2.WINDOW_NORMAL)
	cv2.resizeWindow("Video1", 960, 540)
	cv2.moveWindow("Video1", 0, 0)
else:
	print("Error opening video	file" + video1_file)

if video2_file != "":
	cap2 = cv2.VideoCapture(video2_file)
	if (cap2.isOpened()== True):
		video2_fps    = cap2.get(cv2.CAP_PROP_FPS)
		video2_start  = "00:00:00.000"
		video2_end    = "00:00:00.000"
		video2_skip   = True
		video2_skip_frames = 0

		# Display the resulting frames for video2
		cv2.namedWindow("Video2", cv2.WINDOW_NORMAL)
		cv2.resizeWindow("Video2", 960, 540)
		cv2.moveWindow("Video2", 961, 0)
	else:
		print("Error opening video	file" + video2_file)

# Read until video is completed
while(cap.isOpened()):
	if collect_start == True or collect_end == True:
		if collect_start == True:
			video1_start = video1_timestamp
			if video2_file != "":
				video2_start = video2_timestamp
		elif collect_end == True:
			video1_end = video1_timestamp
			if video2_file != "":
				video2_end = video2_timestamp
		cv2.setWindowTitle("Video1", "Video 1: " + video1_timestamp + " - " + str(int(video1_current_frame)) + "  [" + video1_start + ", " + video1_end + "]")
		if video2_file != "":
			cv2.setWindowTitle("Video2", "Video 2: " + video2_timestamp + " - " + str(int(video2_current_frame)) + "  [" + video2_start + ", " + video2_end + "]")
			print(out_file + "|" + video1_file + "|" + video1_start + "|" + video1_end + "|" + video2_file + "|" + video2_start + "|" + video2_end)
		else:
			print(out_file + "|" + video1_file + "|" + video1_start + "|" + video1_end)

	# Capture frame-by-frame video1
	if run == True or video1_skip == True:
		video1_current_frame = cap.get(cv2.CAP_PROP_POS_FRAMES) - 1
		if video1_skip_frames != 0 and video1_skip_frames != 1:
			cap.set(cv2.CAP_PROP_POS_FRAMES, video1_current_frame + video1_skip_frames)

		ret, video1_frame = cap.read()
		if ret == True:
			video1_current_frame =  cap.get(cv2.CAP_PROP_POS_FRAMES) - 1
			video1_timestamp = str(datetime.datetime.utcfromtimestamp((cap.get(cv2.CAP_PROP_POS_MSEC) - (1000 / video1_fps)) / 1000).strftime('%H:%M:%S.%f'))
			cv2.setWindowTitle("Video1", "Video 1: " + video1_timestamp + " - " + str(int(video1_current_frame)) + "  [" + video1_start + ", " + video1_end + "]")
			cv2.imshow("Video1", video1_frame)

	if video2_file != "":
		# Capture frame-by-frame video2
		if run == True or video2_skip == True:
			video2_current_frame = cap2.get(cv2.CAP_PROP_POS_FRAMES) - 1
			if video2_skip_frames != 0 and video2_skip_frames != 1:
				cap2.set(cv2.CAP_PROP_POS_FRAMES, video2_current_frame + video2_skip_frames)

			ret, video2_frame = cap2.read()
			if ret == True:
				video2_current_frame =  cap2.get(cv2.CAP_PROP_POS_FRAMES) - 1
				video2_timestamp = str(datetime.datetime.utcfromtimestamp((cap2.get(cv2.CAP_PROP_POS_MSEC) - (1000 / video2_fps)) / 1000).strftime('%H:%M:%S.%f'))
				cv2.setWindowTitle("Video2", "Video 2: " + video2_timestamp + " - " + str(int(video2_current_frame)) + "  [" + video2_start + ", " + video2_end + "]")
				cv2.imshow("Video2", video2_frame)

	video1_skip  = False
	video1_skip_frames  = 0

	if video2_file != "":
		video2_skip = False
		video2_skip_frames = 0

	collect_start = False
	collect_end = False

	key = cv2.waitKey(speed) % 256
	if key == 32: #spacebar to toggle run
		speed = 33
		if run == False:
			run = True
		else:
			run = False
	elif key == 27 or key == ord('q'): # Press ESC or Q on keyboard to exit
		break
	elif key == 255: # normally this get returned
		continue
	elif key == ord('x'):
		if speed == 33:
			speed = 1
		else:
			speed = 33
	elif key == ord(']'):
		video2_skip_frames = +1
		video2_skip = True
	elif key == ord('['):
		video2_skip_frames = -1
		video2_skip = True
	elif key == ord('}'):
		video2_skip_frames = +125
		video2_skip = True
	elif key == ord('{'):
		video2_skip_frames = -125
		video2_skip = True
	elif key == ord('.'):
		video1_skip_frames = +1
		video1_skip = True
	elif key == ord(','):
		video1_skip_frames = -1
		video1_skip = True
	elif key == ord('>'):
		video1_skip_frames = +125
		video1_skip = True
	elif key == ord('<'):
		video1_skip_frames = -125
		video1_skip = True
	elif key == ord('n'):
		video1_skip_frames = +1
		video1_skip = True
		video2_skip_frames = +1
		video2_skip = True
	elif key == ord('p'):
		video1_skip_frames = -1
		video1_skip = True
		video2_skip_frames = -1
		video2_skip = True
	elif key == ord('N'):
		video1_skip_frames = +125
		video1_skip = True
		video2_skip_frames = +125
		video2_skip = True
	elif key == ord('P'):
		video1_skip_frames = -125
		video1_skip = True
		video2_skip_frames = -125
		video2_skip = True
	elif key == ord('s'):
		collect_start = True
	elif key == ord('e'):
		collect_end = True
	else:
		print(key)

# When everything done, release the video capture object
cap.release()
if video2_file != "":
	cap2.release()

# Closes all the frames
cv2.destroyAllWindows()
