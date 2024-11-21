import spacy
import pandas as pd
from pathlib import Path
from tqdm import tqdm

# Download Portuguese language model
# Run once: python -m spacy download pt_core_news_lg
nlp = spacy.load('pt_core_news_lg')

# Define o número de palavras a serem geradas
NUM_PALAVRAS = 50

# Create dictionary from built-in vectors
words_meanings = []

# Initialize tqdm without total
with tqdm(nlp.vocab.vectors.items(), desc="Processando palavras") as pbar:
    for word, vector in pbar:
        if len(words_meanings) >= NUM_PALAVRAS:
            break
        word_text = nlp.vocab.strings[word]
        if word_text.isalpha() and len(word_text) > 2:
            # Get word context from most similar words
            similar = nlp.vocab.vectors.most_similar(vector.reshape(1, -1), n=4)
            meaning = ", ".join([nlp.vocab.strings[w] for w in similar[0][0] if w != word])
            words_meanings.append({
                "palavra": word_text,
                "significado": meaning
            })
            # Atualiza o postfix com o número de palavras coletadas
            pbar.set_postfix({'Coletadas': len(words_meanings)})

# Save to TXT file
with open("palavras_portugues.txt", "w", encoding="utf-8") as file:
    for item in words_meanings:
        file.write(f"{item['palavra']}: {item['significado']}\n")

print(f"Generated {len(words_meanings)} Portuguese words and meanings in 'palavras_portugues.txt'")