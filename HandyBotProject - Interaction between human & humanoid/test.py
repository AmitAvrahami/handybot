import pickle
import mediapipe as mp
import cv2
import numpy as np
import os
import re
import warnings
import google.generativeai as genai
warnings.filterwarnings("ignore", category=UserWarning, module='google.protobuf.symbol_database')


def load_model_from_file(file):
    model_dict = pickle.load(open(file, 'rb'))

    return model_dict

def recognize_sequence(predict_sign , word_sequence):

    if predict_sign == 'space':
        word_sequence += ' '
    elif predict_sign == 'del' and len(word_sequence) > 0:
        word_sequence = word_sequence[:-1]  # Remove the last character
    else:
        word_sequence += predict_sign

    return word_sequence

def send_query_to_ai_model(query):
    model_instructions = "Please make the response 10 words or"
    genai.configure(api_key='AIzaSyBLbFTlEL1hBmEm3fU4o47l7aGT7L5mMFw') 
    g_model = genai.GenerativeModel(model_name="gemini-1.5-flash")
    response = g_model.generate_content([query.join(model_instructions)])

    cleaned_text = re.sub(r'[^\w\s]', '', response.text)  
    cleaned_text = cleaned_text.split() 
    cleaned_text = ' '.join(cleaned_text[:10]) 

    return cleaned_text

def load_model_and_categories(model_path, data_path):
    model_dict = load_model_from_file(model_path)
    model = model_dict['model']
    categories = os.listdir(data_path)
    return model, categories

def initialize_mediapipe_and_camera():
    mp_hands = mp.solutions.hands
    hands = mp_hands.Hands(max_num_hands=1, static_image_mode=True, min_detection_confidence=0.3)
    mp_drawing = mp.solutions.drawing_utils
    mp_drawing_styles = mp.solutions.drawing_styles
    cap = cv2.VideoCapture(0)
    return hands, mp_drawing, mp_drawing_styles, cap

def process_frame(frame, hands, mp_drawing, mp_hands, model, categories):
    data_aux = []
    x_ = []
    y_ = []
    frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    results = hands.process(frame_rgb)
    
    if results.multi_hand_landmarks:
        for hand_landmarks in results.multi_hand_landmarks:
            mp_drawing.draw_landmarks(
                frame,
                hand_landmarks,
                mp_hands.HAND_CONNECTIONS,
                mp_drawing.DrawingSpec(color=(0, 0, 255), thickness=2, circle_radius=2),
                mp_drawing.DrawingSpec(color=(0, 255, 0), thickness=2, circle_radius=2)
            )
            for lm in hand_landmarks.landmark:
                data_aux.append(lm.x)
                data_aux.append(lm.y)
                x_.append(lm.x)
                y_.append(lm.y)

        x1 = int(min(x_) * frame.shape[1])
        y1 = int(min(y_) * frame.shape[0])
        x2 = int(max(x_) * frame.shape[1])
        y2 = int(max(y_) * frame.shape[0])

        prediction = model.predict([np.asarray(data_aux)])
        predicted_label = categories[int(prediction[0])]

        cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 0, 0), 4)
        cv2.putText(frame, predicted_label, (x1, y1), cv2.FONT_HERSHEY_SIMPLEX, 1.3, (0, 0, 0), 3, cv2.LINE_AA)
        return frame, predicted_label
    return frame, None

def main():
    model, categories = load_model_and_categories('./model2.p', './data/asl_alphabet_train')
    hands, mp_drawing, mp_drawing_styles, cap = initialize_mediapipe_and_camera()
    text = ""

    while True:
        ret, frame = cap.read()
        if not ret:
            break

        frame, predicted_label = process_frame(frame, hands, mp_drawing, mp.solutions.hands, model, categories)
        
        cv2.imshow('frame', frame)
        
        if cv2.getWindowProperty('frame', cv2.WND_PROP_VISIBLE) < 1:
            break

        key = cv2.waitKey(25) & 0xFF
        if key == ord('q'):
            break
        elif key == ord('r') and predicted_label:  # כאשר לוחצים על 'r'
            text = recognize_sequence(predicted_label, text)
            print(text)
        elif key == ord('s'):
            response = send_query_to_ai_model(text)
            print(response)
            text = ""

    response = send_query_to_ai_model(text)
    cap.release()
    cv2.destroyAllWindows()
    print(response)

if __name__ == "__main__":
    main()