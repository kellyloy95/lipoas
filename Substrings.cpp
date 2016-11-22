#include <string>
#include <sstream>
#include "interface.h"
using namespace std;

entrenceData GetNewText(entrenceData newEntrenceData){
    string currentSubstring;//текущая подстрока
    string tempSubstring;//подстрока из текста для сравнения с текущей подстрокой
    string stringForReplacing;//подстрока, формируемая для замены подстроки из текста, в случае повтора
    int currentSubStringSize = newEntrenceData.text.size()/2;//размер текущей подстроки
    while (currentSubStringSize > newEntrenceData.subStringLenth) {
        for (int i = 0; i < newEntrenceData.text.size() - currentSubStringSize + 1; i++) //цикл на первый символ
          {
            currentSubstring = newEntrenceData.text.substr(i,currentSubStringSize);
            if(currentSubstring.find_first_of('{') == -1 && currentSubstring.find_first_of('}') == -1 ) {
                if (currentSubstring.find_first_of(',') == -1){
                    for (int j = currentSubstring.size() +i; j < newEntrenceData.text.size() - currentSubStringSize+1; j++) {
                        tempSubstring = newEntrenceData.text.substr(j,currentSubStringSize);
                        if (tempSubstring == currentSubstring){
                            ostringstream streamForSubstringBeginIndex;//число в строку перевести, индекс начала повторяющейся строки
                            ostringstream streamForSubstringSize;// размер повторяющейся строки
                            streamForSubstringBeginIndex << i;
                            streamForSubstringSize << currentSubstring.size();
                            stringForReplacing = "{" +streamForSubstringBeginIndex.str() + "," + streamForSubstringSize.str() + "}";// результат
                            newEntrenceData.text.replace(j,currentSubstring.size(), stringForReplacing);
                        }
                    }
                }
                else {
                    int rightBrackets = 0;//количество «правых» скобочек от начала до проверяемой подстроки
                    int leftBrackets = 0;
                    for (int k = currentSubstring.size() +i-1; k > 0; k--) {
                        if (newEntrenceData.text[k] == '}') {
                            rightBrackets++;
                        }
                        if (newEntrenceData.text[k] == '{') {
                            leftBrackets++;
                        }
                    }
                    if (leftBrackets == rightBrackets) {
                        for (int j = currentSubstring.size() +i; j < newEntrenceData.text.size() - currentSubStringSize+1; j++) {
                            tempSubstring = newEntrenceData.text.substr(j,currentSubStringSize);
                            if (tempSubstring == currentSubstring) {
                                ostringstream streamForSubstringBeginIndex;
                                ostringstream streamForSubstringSize;
                                streamForSubstringBeginIndex << i;
                                streamForSubstringSize << currentSubstring.size();
                                stringForReplacing = "{" +streamForSubstringBeginIndex.str() + "," + streamForSubstringSize.str() + "}";
                                newEntrenceData.text.replace(j,currentSubstring.size(), stringForReplacing);
                            }
                        }
                    }
                }
                
            }
        }
        currentSubStringSize--;
    }
    return newEntrenceData;
}
