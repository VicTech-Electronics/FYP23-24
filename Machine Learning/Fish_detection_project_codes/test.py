import cv2 as cv

# frame file path for testing
fish_image_path = "./images/"

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

image = cv.imread(fish_image_path + "image9.jpg")
counter = 0
lengths = []
(_, confidences, boxes) = model.detect(image)
for confidence, box in zip(confidences, boxes):
    x, y, w, h = box
    _x = x + w
    _y = y + h

    cv.rectangle(img=image, pt1=(x, y), pt2=(_x, _y), color=(0, 255, 0), thickness=1)
    cv.putText(
        img=image,
        text=model_label,
        org=(x, y + 3),
        fontFace=cv.FONT_ITALIC,
        fontScale=0.5,
        color=(0, 255, 0),
        thickness=1,
    )

    counter += 1
    lengths.append(int(_x - x))


print(f'There are {counter} Fishes')
print('Confidences in percentage:')
print(list(map(int, confidences * 100)))
print('Lengths in pixels:')
print(lengths)

cv.imshow("Screen", image)
cv.waitKey(0)
cv.destroyAllWindows()
