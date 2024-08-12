import cv2 as cv

# Files path location
model_weights = "./Model/yolov3.weights"
model_configurations = "./Model/yolov3.cfg"
model_label = "Fish"

net = cv.dnn.readNet(model_weights, model_configurations)
model = cv.dnn_DetectionModel(net)
model.setInputParams(
    size=(320, 320),
    scale=1 / 255,
)


cap = cv.VideoCapture(0)
while True:
    is_captured, frame = cap.read()
    if is_captured is None:
        break

    (_, confidences, boxes) = model.detect(frame)
    for confidence, box in zip(confidences, boxes):
        x, y, w, h = box
        cv.rectangle(
            img=frame, pt1=(x, y), pt2=(x + w, y + h), color=(0, 255, 0), thickness=1
        )
        cv.putText(
            img=frame,
            text=model_label,
            org=(x, y - 3),
            fontFace=cv.FONT_ITALIC,
            fontScale=0.5,
            color=(0, 255, 0),
            thickness=1,
        )

    cv.imshow("Screen", frame)
