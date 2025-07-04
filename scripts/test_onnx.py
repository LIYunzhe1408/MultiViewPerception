import onnxruntime as ort
ort.InferenceSession("./model/yolov5s.onnx")
print("ONNX model loaded!")
