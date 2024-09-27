import socket
import pyaudio  # pip install pyaudio
import numpy as np  # pip install numpy

# Configuration variables
UDP_IP = "0.0.0.0"       # Listen on all available interfaces
UDP_PORT = 16500         # Port number to listen on
BUFFER_SIZE = 400        # Buffer size for UDP packets
GAIN = 3.0               # Gain factor for volume adjustment

# Initialize PyAudio for audio playback
audio = pyaudio.PyAudio()  # Initialize PyAudio
stream = (
    audio.open(
        format=pyaudio.paInt16,  # 16-bit audio format
        channels=2,              # Stereo audio
        rate=16000,              # Sampling rate of 16kHz
        output=True              # Set stream to output mode
    )
)

# Set up UDP socket for receiving audio data
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # Create UDP socket
sock.bind((UDP_IP, UDP_PORT))  # Bind to specified IP and port
print(
    f"Listening on UDP port {UDP_PORT}..."
    " Please ensure this port is whitelisted."
)  # Notify that the port should be whitelisted

try:
    while True:
        data, addr = sock.recvfrom(BUFFER_SIZE)  # Receive UDP packet and address
        print(f"Received data from {addr}")       # Notify when data is received
        if (data_length := len(data)) == BUFFER_SIZE:
            # Convert byte data to numpy array for processing
            audio_data = np.frombuffer(data, dtype=np.int16)
            # Apply gain using numpy
            audio_data = np.clip(audio_data * GAIN, -32768, 32767).astype(np.int16)
            # Convert back to bytes and play the received audio
            stream.write(audio_data.tobytes())     # Play the received audio
except KeyboardInterrupt:
    print("Stopping the server...")               # Notify that the server is stopping
except (Exception,) as e:
    print(f"An error occurred: {e}")             # Print any exceptions
finally:
    # Clean up resources
    stream.stop_stream()                         # Stop the audio stream
    stream.close()                               # Close the audio stream
    audio.terminate()                            # Terminate PyAudio
    sock.close()                                 # Close the socket
