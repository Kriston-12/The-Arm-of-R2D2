import cv2
import torch

import serial
import json
import time


scaling_mult = None
def process_yolo_output(yolo_output):
    """
    Process YOLO output to generate a dictionary with object types as keys
    and relative 2D locations to the top left corner as values.
    """
    global scaling_mult
    objects_dict = {}

    if len(yolo_output) > 0:
        for detection in yolo_output:
            for index, row in yolo_output.iterrows():
                name = row['name']
                confi = row['confidence']

                if name == "mouse":
                    x0, x1, y0, y1 = row['xmin'], row['xmax'], row['ymin'], row['ymax']
                    y_dif = y1 - y0
                    scaling_mult = y_dif / 9.2

                if confi > 0.3:
                    x0, x1, y0, y1 = row['xmin'], row['xmax'], row['ymin'], row['ymax']
                    xavg = (int(x0 + x1))/2
                    yavg = (int(y0 + y1))/2
                    if scaling_mult is not None:
                        xavg /= scaling_mult
                        yavg /= scaling_mult

                    object_location = (xavg, yavg)  # Top left corner coordinates
                    objects_dict[name] = [xavg, yavg]

    return objects_dict

def serialized_dict(dict):
    serialized_data = json.dumps(dict) + "\n"
    return serialized_data


# Load YOLOv5 model
model = torch.hub.load('ultralytics/yolov5:v6.0', 'yolov5s')  # or yolov5m, yolov5l, yolov5x, etc.

# Set the camera index (0 for default camera)
camera_index = 1

# Open a connection to the camera
cap = cv2.VideoCapture(camera_index)

# Open serial port
ser = serial.Serial('COM5', 9600)  # Adjust port and baud rate as needed

while True:
    # Capture frame-by-frame
    ret, frame = cap.read()

    # Convert BGR to RGB
    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

    # Perform inference
    results = model(rgb_frame)

    # Process YOLO output
    objects_dict = process_yolo_output(results.pandas().xyxy[0])

    #ser.write(serialized_dict(objects_dict).encode())

    # Print the resulting dictionary
    print(objects_dict)

    # Render bounding boxes on the frame
    annotated_frame = results.render()[0]

    # Convert annotated frame back to BGR for displaying with OpenCV
    bgr_annotated_frame = cv2.cvtColor(annotated_frame, cv2.COLOR_RGB2BGR)

    # Display the resulting frame
    cv2.imshow('YOLOv5 Object Detection', bgr_annotated_frame)

    # Break the loop if 'q' key is pressed
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the camera and close all windows
cap.release()
cv2.destroyAllWindows()
