
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <windows.h>
using namespace std;


void getMenu() {
    cout << "# MENU #" << endl;
    cout << "1- TAHMIN ET\n2- HARF TAHMIN ET\n3- IPUCU AL\n4- CIKIS\nSECIMINIZ: ";
}


const string correctUsername = "admin";
const string correctPassword = "1234";

bool login() {
    string username, password;

    cout << "Kullanici adi: ";
    cin >> username;

    cout << "Parola: ";
    cin >> password;

    if (username == correctUsername && password == correctPassword) {
        cout << "Giris basarili!" << endl;
        return true;
    }
    else {
        cout << "Giris basarisiz!" << endl;
        return false;
    }
}

class SoruYoneticisi {

private:
    struct Question {
        string questionText;
        string answer;
        string tip;
    };
    const string questionsFileName = "sorular.txt";
    vector<Question> questions;

    void writeQuestionToFile(const Question& question) {
        ofstream outFile(questionsFileName, ios::app);
        if (outFile.is_open()) {
            outFile << "SORU: " << question.questionText << endl;
            outFile << "CEVAP: " << question.answer << endl;
            outFile << "IPUCU: " << question.tip << endl;
            outFile << "---" << endl;
            outFile.close();
            cout << "Soru dosyaya eklendi!" << endl;
        }
        else {
            cout << "Dosya acilamadi!" << endl;
        }
    }

    void drawHangman(int wrongGuesses) {
        if (wrongGuesses == 5) {
            cout << " ___ " << endl;
            cout << " |       | " << endl;
            cout << " |       O " << endl;
            cout << " |      /|\\ " << endl;
            cout << " |      / \\ " << endl;
            cout << " |          " << endl;
            cout << "|__       " << endl;
        }
        else if (wrongGuesses == 4) {
            cout << " ___ " << endl;
            cout << " |       | " << endl;
            cout << " |       O " << endl;
            cout << " |      /|\\ " << endl;
            cout << " |      /   " << endl;
            cout << " |          " << endl;
            cout << "|__       " << endl;
        }
        else if (wrongGuesses == 3) {
            cout << " ___ " << endl;
            cout << " |       | " << endl;
            cout << " |       O " << endl;
            cout << " |      /|\\ " << endl;
            cout << " |           " << endl;
            cout << " |          " << endl;
            cout << "|__       " << endl;
        }
        else if (wrongGuesses == 2) {
            cout << " ___ " << endl;
            cout << " |       | " << endl;
            cout << " |       O " << endl;
            cout << " |      /|  " << endl;
            cout << " |          " << endl;
            cout << " |          " << endl;
            cout << "|__       " << endl;
        }
        else if (wrongGuesses == 1) {
            cout << " ___ " << endl;
            cout << " |       | " << endl;
            cout << " |       O " << endl;
            cout << " |       |  " << endl;
            cout << " |          " << endl;
            cout << " |          " << endl;
            cout << "|__       " << endl;
        }
        else if (wrongGuesses == 0) {
            cout << " ___ " << endl;
            cout << " |       | " << endl;
            cout << " |       O " << endl;
            cout << " |          " << endl;
            cout << " |          " << endl;
            cout << " |          " << endl;
            cout << "|__       " << endl;
        }
    }

public:
    void addQuestion() {
        Question question;

        cout << "Soru metnini giriniz: ";
        cin.ignore(); // Önceki giriþi temizlemek için
        getline(cin, question.questionText);

        cout << "Cevap: ";
        getline(cin, question.answer);

        cout << "Ýpucu: ";
        getline(cin, question.tip);

        writeQuestionToFile(question);
        cout << "Soru baþarýyla eklendi!" << endl;

        char choice;
        cout << "Soru eklemeye devam etmek istiyor musunuz? (E/H): ";
        cin >> choice;

        if (choice == 'E' || choice == 'e') {
            addQuestion(); // Soru eklemeye devam et
        }
       
    }

public:
    
    
    void playHangman(SoruYoneticisi& soruYoneticisi) {
        bool ipucuAlindi = false;

        while (true) {
            // Ýlk rastgele soruyu al
            vector<SoruYoneticisi::Question> loadedQuestions = soruYoneticisi.loadQuestionsFromFile();
            if (loadedQuestions.empty()) {
                cout << "Henuz soru eklenmemis!" << endl;
                return;
            }

            srand(time(nullptr)); // Rastgelelik için seed ayarý
            int randomIndex = rand() % loadedQuestions.size();
            SoruYoneticisi::Question randomQuestion = loadedQuestions[randomIndex];

            string secretWord = randomQuestion.answer; // Gizli kelime

            cout << endl <<"Soru: " << randomQuestion.questionText << endl;

            // Menüyü göster ve iþlem seçeneðini al
            menu:
            up:
            int secim;
            cout << endl << "Hangi tip tahmin yapmak istersiniz?" << endl;
            cout << endl << "1- TAHMIN ET\n2- HARF TAHMIN ET\n3- IPUCU AL\n4- CIKIS\nSECIMINIZ: " << endl;
            cin >> secim;

            switch (secim) {
            case 1: {
                string guess;
                cout << "Cevap: ";
                cin >> guess;

                if (guess == randomQuestion.answer) {
                    cout << "Tebrikler, dogru cevap!" << endl;
                }
                else {
                    cout << "Uzgunum, yanlis cevap. Dogru cevap: " << randomQuestion.answer << endl;
                }
            }
                  break;

            case 2: {
                string guessedWord(secretWord.size(), '_'); // Tahmin edilen harf ve boþluklarý tutan string
                int wrongGuesses = 0; // Yanlýþ tahmin sayýsý
                int maxWrongGuesses = 6; // Maksimum yanlýþ tahmin sayýsý

                while (wrongGuesses < maxWrongGuesses && guessedWord != secretWord) {
                    cout << "Tahmin edilen kelime: " << guessedWord << endl;

                    char guess;
                    cout << "Ana menuye donup.Tahminde bulunmak icin  icin '*' tusuna basin: " << endl;
                    cout << "Bir harf tahmin edin: " << endl;

                    cin >> guess;

                    if (guess == '*')
                    {
                        goto menu;
                    }

                    bool correctGuess = false;
                    for (int i = 0; i < secretWord.size(); ++i) {
                        if (secretWord[i] == guess) {
                            guessedWord[i] = guess;
                            correctGuess = true;
                        }
                    }

                    if (!correctGuess) {
                        ++wrongGuesses;
                        cout << "Yanlis tahmin! Kalan hak: " << maxWrongGuesses - wrongGuesses << endl;
                        // Adam asma çizimini ekrana çizdir
                        drawHangman(wrongGuesses);
                    }
                }

                if (guessedWord == secretWord) {
                    cout << "Tebrikler, kelimeyi buldunuz! Kelime: " << secretWord << endl;
                }
                else {
                    cout << "Uzgunum, kelimeyi bulamadiniz. Dogru kelime: " << secretWord << endl;
                }
            }
                  break;

            case 3: {
                if (!ipucuAlindi) {
                    cout << "IPUCU: " << randomQuestion.tip << endl;
                    ipucuAlindi = true; // Ýpucu alýndý olarak iþaretle
                    goto up;
                }
                else {
                    cout << "Zaten bir ipucu aldýnýz!" << endl;
                }
            }
                  break;

            case 4:
                cout << "Programdan cikis yapiliyor..." << endl;
                exit(0); // Programý sonlandýr
                break;

            default:
                cout << "Gecersiz secim!" << endl;
                break;
            }
        }
    }
public:
    vector<Question> loadQuestionsFromFile() {
        vector<Question> loadedQuestions;
        ifstream inFile(questionsFileName);
        if (inFile.is_open()) {
            Question question;
            string line;
            while (getline(inFile, line)) {
                if (line.find("SORU: ") == 0) {
                    question.questionText = line.substr(6);
                    getline(inFile, line);
                    question.answer = line.substr(7);
                    getline(inFile, line);
                    question.tip = line.substr(6);
                    loadedQuestions.push_back(question);
                }
            }
            inFile.close();
        }
        else {
            cout << "Dosya acilamadi!" << endl;
        }
        return loadedQuestions;
    }

};
int main() {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD savedAttributes;

    // Geçerli konsol renk ayarlarýný al
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    savedAttributes = consoleInfo.wAttributes;

    srand(time(nullptr)); // Rastgelelik için seed ayarý
    SoruYoneticisi soruYoneticisi;

    while (true) {
        int secim;
        start:
        cout << "MENU" << endl;
        cout << "1. Giris Yap" << endl;
        cout << "2. Oyna" << endl;
        cout << "3. Cikis" << endl;
        cout << "Seciminizi yapiniz: ";
        cin >> secim;

        switch (secim) {
            case 1:
                if (login()) {
                    while (true) {
                        cout << "MENU" << endl;
                        cout << "1. Soru Ekle" << endl;
                        cout << "2. Oyna" << endl;
                        cout << "3. Ana Menu" << endl;
                        cout << "Seciminizi yapiniz: ";
                        cin >> secim;

                        switch (secim) {
                            case 1:
                                soruYoneticisi.addQuestion();
                                break;

                            case 2:
                                soruYoneticisi.playHangman(soruYoneticisi);
                                break;

                            case 3:
                                goto start;

                            default:
                                cout << "Gecersiz secim!" << endl;
                                break;
                        }
                    }
                }
                break;

            case 2:
                soruYoneticisi.playHangman(soruYoneticisi);
                break;

            case 3:
                exit(0);
              
            default:
                cout << "Gecersiz secim!" << endl;
                break;
        }
    }

    return 0;
}