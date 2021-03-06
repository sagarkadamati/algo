# importing libraries
import cv2
import time
import datetime
import os
import sys
import math
import ntpath
import numpy as np
import pyaudio
import wave

video1_file = sys.argv[1]
try:
	video2_file = sys.argv[2]
except:
	video2_file = ""
try:
	out_file = sys.argv[3]
except IndexError:
	out_file = ntpath.basename(video1_file)

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
	video1_start_frame = 0
	video1_end_frame = 0
	audio = 0

	Audio1_file = wave.open('first.wav', 'rb')

	# initialize audio
	py_audio = pyaudio.PyAudio()
	stream = py_audio.open(format=py_audio.get_format_from_width(Audio1_file.getsampwidth()),
					channels=Audio1_file.getnchannels(),
					rate=Audio1_file.getframerate(),
					output=True)

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
		video2_start_frame = 0
		video2_end_frame = 0

		Audio2_file = wave.open('second.wav', 'rb')

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
			video1_start_frame = video1_current_frame
			if video2_file != "":
				video2_start = video2_timestamp
				video2_start_frame = video2_current_frame
		elif collect_end == True:
			video1_end = video1_timestamp
			video1_end_frame = video1_current_frame
			if video2_file != "":
				video2_end = video2_timestamp
				video2_end_frame = video2_current_frame
		cv2.setWindowTitle("Video1", "Video 1: " + video1_timestamp + " - " + str(int(video1_current_frame)) + "  [" + video1_start + ", " + video1_end + "]")
		if video2_file != "":
			cv2.setWindowTitle("Video2", "Video 2: " + video2_timestamp + " - " + str(int(video2_current_frame)) + "  [" + video2_start + ", " + video2_end + "]")
			print(out_file + "|" + video1_file + "|" + video1_start + "|" + video1_end + "|" + video2_file + "|" + video2_start + "|" + video2_end)
		else:
			print(out_file + "|" + video1_file + "|" + video1_start + "|" + video1_end)

	aplay = False
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
				win2_title = "Video 2: " + video2_timestamp + " - " + str(int(video2_current_frame)) + "  [" + video2_start + ", " + video2_end + "]"

				if run == True and speed == 33 and video2_file != "":
					if  audio == 2  or (audio == 0 and video2_current_frame >= video2_start_frame):
						# skip unwanted frames
						audio2_current_frame = int(video2_current_frame * Audio2_file.getframerate() / video2_fps)
						Audio2_file.setpos(audio2_current_frame)

						# write desired frames to audio buffer
						n_frames = int(Audio2_file.getframerate() / video2_fps)
						audio_frames = Audio2_file.readframes(n_frames)

						video2_current_frame =  cap2.get(cv2.CAP_PROP_POS_FRAMES) - 1
						video2_timestamp = str(datetime.datetime.utcfromtimestamp((cap2.get(cv2.CAP_PROP_POS_MSEC) - (1000 / video2_fps)) / 1000).strftime('%H:%M:%S.%f'))
						win2_title += " - [Audio]"
						aplay = True

				cv2.setWindowTitle("Video2", win2_title)
				cv2.imshow("Video2", video2_frame)

	# Capture frame-by-frame video1
	if run == True or video1_skip == True:
		video1_current_frame = cap.get(cv2.CAP_PROP_POS_FRAMES) - 1
		if video1_skip_frames != 0 and video1_skip_frames != 1:
			cap.set(cv2.CAP_PROP_POS_FRAMES, video1_current_frame + video1_skip_frames)

		ret, video1_frame = cap.read()
		if ret == True:
			video1_current_frame =  cap.get(cv2.CAP_PROP_POS_FRAMES) - 1
			video1_timestamp = str(datetime.datetime.utcfromtimestamp((cap.get(cv2.CAP_PROP_POS_MSEC) - (1000 / video1_fps)) / 1000).strftime('%H:%M:%S.%f'))
			win1_title = "Video 1: " + video1_timestamp + " - " + str(int(video1_current_frame)) + "  [" + video1_start + ", " + video1_end + "]"

			if run == True and speed == 33 and aplay == False:
				# skip unwanted frames
				audio1_current_frame = int(video1_current_frame * Audio1_file.getframerate() / video1_fps)
				Audio1_file.setpos(audio1_current_frame)

				# write desired frames to audio buffer
				n_frames = int(Audio1_file.getframerate() / video1_fps)
				audio_frames = Audio1_file.readframes(n_frames)

				video1_current_frame =  cap.get(cv2.CAP_PROP_POS_FRAMES) - 1
				video1_timestamp = str(datetime.datetime.utcfromtimestamp((cap.get(cv2.CAP_PROP_POS_MSEC) - (1000 / video1_fps)) / 1000).strftime('%H:%M:%S.%f'))
				win1_title += " - [Audio]"

			cv2.setWindowTitle("Video1", win1_title)
			cv2.imshow("Video1", video1_frame)

	if run == True and speed == 33:
		stream.write(audio_frames)

	video1_skip  = False
	video1_skip_frames  = 0

	if video2_file != "":
		video2_skip = False
		video2_skip_frames = 0

	collect_start = False
	collect_end = False

	# key = cv2.waitKey(speed) % 256
	key = cv2.waitKey(1) % 256
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
	elif key == ord('a'):
		if video2_file != "":
			if audio == 0:
				audio = 1
			elif audio == 1:
					audio = 2
			else:
				if video2_current_frame >= video2_start_frame:
					audio = 1
				else:
					audio = 0
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

# When everything done, release resources
Audio1_file.close()
cap.release()
if video2_file != "":
	Audio2_file.close()
	cap2.release()

stream.close()
py_audio.terminate()

# Closes all the frames
cv2.destroyAllWindows()
