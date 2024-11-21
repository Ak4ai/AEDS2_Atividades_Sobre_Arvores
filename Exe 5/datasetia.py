import nltk
from nltk.corpus import wordnet
from googletrans import Translator
from tqdm import tqdm
import os

# Download the necessary NLTK data
nltk.download('wordnet')

def translate_word(word, definitions, translator):
    translated_definitions = []
    for defn in definitions:
        try:
            translated_text = translator.translate(defn, src='en', dest='pt').text
            translated_definitions.append(translated_text)
        except Exception as e:
            print(f"Erro ao traduzir definição '{defn}' para a palavra '{word}': {e}")
    try:
        translated_word = translator.translate(word, src='en', dest='pt').text
        return translated_word, translated_definitions
    except Exception as e:
        print(f"Erro ao processar a palavra '{word}': {e}")
        return None

def main():
    # Inicializar o tradutor
    translator = Translator()

    # Ler palavras do arquivo google-10000-english-usa.txt
    with open("google-10000-english-usa.txt", "r") as file:
        words = [line.strip() for line in file.readlines()]

    word_definitions = {}
    progress_bar = tqdm(total=len(words))

    for word in words:
        definitions = [syn.definition() for syn in wordnet.synsets(word)]
        result = translate_word(word, definitions, translator)
        if result:
            translated_word, translated_definitions = result
            word_definitions[translated_word] = translated_definitions
            progress_bar.update(1)  # Atualizar a barra de progresso

    progress_bar.close()

    # Salvar o dataset em um arquivo
    with open("dicionario.txt", "w") as file:
        for word, definitions in word_definitions.items():
            file.write(f"{word}: {definitions}\n")

    print("Dataset de palavras gerado e salvo em dicionario.txt")

    # Desligar o PC
    os.system("shutdown now")

if __name__ == "__main__":
    main()