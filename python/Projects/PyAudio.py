import pyaudio
import wave

print (wave.__file__)

# set desired values
start = 7
length = 25

# open wave file
wave_file = wave.open('first.wav', 'rb')

# initialize audio
py_audio = pyaudio.PyAudio()
stream = py_audio.open(format=py_audio.get_format_from_width(wave_file.getsampwidth()),
                       channels=wave_file.getnchannels(),
                       rate=wave_file.getframerate(),
                       output=True)

# skip unwanted frames
n_frames = int(start * wave_file.getframerate())
wave_file.setpos(n_frames)

# write desired frames to audio buffer
n_frames = int(length * (wave_file.getframerate() / 25))
frames = wave_file.readframes(n_frames)
stream.write(frames)

# close and terminate everything properly
stream.close()
py_audio.terminate()
wave_file.close()












# import os
# import scipy.io.wavfile as wav

# FileName = '001 Prashasti.wav'
# data = wav.read(FileName)

# print(data)
















# import numpy as np
# import sys
# import librosa
# import scipy
# import matplotlib.pyplot as plt
# from matplotlib import cm

# #   Input parameter
# #   relative_path_to_file

# if len(sys.argv) < 1:
#     print "Missing Arguments!"
#     print "python spectogram_librosa.py path_to_audio_file"
#     sys.exit()

# path = sys.argv[1]
# abs_path = os.path.abspath(path)
# spectogram_dnn = "spectogram"

# if not os.path.exists(spectogram_dnn):
#     print "spectogram_dnn folder didn't exist!"
#     os.makedirs(spectogram_dnn)
#     print "Created!"

# y,sr = librosa.load(abs_path,sr=16000)
# D = librosa.logamplitude(np.abs(librosa.core.stft(y, win_length=400, hop_length=160, window=scipy.signal.hanning,center=False)), ref_power=np.max)
# librosa.display.specshow(D,sr=16000,hop_length=160, x_axis='time', y_axis='log', cmap=cm.jet)
# plt.colorbar(format='%+2.0f dB')
# plt.title('Log power spectrogram')
# plt.show()
# raw_input()

# sys.exit()