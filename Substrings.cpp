#include <string>
#include <sstream>
#include "interface.h"
using namespace std;

entrenceData GetNewText(entrenceData newEntrenceData){
    string currentSubstring;//������� ���������
    string tempSubstring;//��������� �� ������ ��� ��������� � ������� ����������
    string stringForReplacing;//���������, ����������� ��� ������ ��������� �� ������, � ������ �������
    int currentSubStringSize = newEntrenceData.text.size()/2;//������ ������� ���������
    while (currentSubStringSize > newEntrenceData.subStringLenth) {
        for (int i = 0; i < newEntrenceData.text.size() - currentSubStringSize + 1; i++) //���� �� ������ ������
          {
            currentSubstring = newEntrenceData.text.substr(i,currentSubStringSize);
            if(currentSubstring.find_first_of('{') == -1 && currentSubstring.find_first_of('}') == -1 ) {
                if (currentSubstring.find_first_of(',') == -1){
                    for (int j = currentSubstring.size() +i; j < newEntrenceData.text.size() - currentSubStringSize+1; j++) {
                        tempSubstring = newEntrenceData.text.substr(j,currentSubStringSize);
                        if (tempSubstring == currentSubstring){
                            ostringstream streamForSubstringBeginIndex;//����� � ������ ���������, ������ ������ ������������� ������
                            ostringstream streamForSubstringSize;// ������ ������������� ������
                            streamForSubstringBeginIndex << i;
                            streamForSubstringSize << currentSubstring.size();
                            stringForReplacing = "{" +streamForSubstringBeginIndex.str() + "," + streamForSubstringSize.str() + "}";// ���������
                            newEntrenceData.text.replace(j,currentSubstring.size(), stringForReplacing);
                        }
                    }
                }
                else {
                    int rightBrackets = 0;//���������� �������� �������� �� ������ �� ����������� ���������
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
