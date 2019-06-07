#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <wctype.h>



wchar_t* getMask(wchar_t* mask, wchar_t* word, int maxlen){
    setlocale(LC_CTYPE, "");

    int lstar_inp = 0;
    int rstar_inp = 0;
    if (mask[0] == '*') lstar_inp = 1;
    if (mask[wcslen(mask) - 1] == '*') rstar_inp = 1;
    mask[wcslen(mask) - rstar_inp] = 0;
    mask += lstar_inp;
    
    int mask_len = wcslen(mask);
    int word_len = wcslen(word);

    wchar_t* befTmp = malloc((maxlen+1)*sizeof(wchar_t));           // ВЫДЕЛЕННАЯ ПАМЯТЬ BEFTMP
    wchar_t* aftTmp = malloc((maxlen+1)*sizeof(wchar_t));           // ВЫДЕЛЕННАЯ ПАМЯТЬ AFTTMP
    int maxCongs = 0;
    wchar_t* unstarMask = malloc((maxlen+3)*sizeof(wchar_t));       // ВЫДЕЛЕННАЯ ПАМЯТЬ UNSTARMASK
    wchar_t* outMask = malloc((maxlen+3)*sizeof(wchar_t));          // ВЫДЕЛЕННАЯ ПАМЯТЬ OUTMASK
    wchar_t* emptyMask = malloc((maxlen+1)*sizeof(wchar_t));        // ВЫДЕЛЕННАЯ ПАМЯТЬ EMPTYMASK
    int lstar;
    int lstar_tmp;
    int rstar;
    int rstar_tmp;
    for(int i = -word_len + 1; /*i < 1*/ i < mask_len; i++){
        lstar_tmp = 0;
        rstar_tmp = 0;
        wchar_t* upStr = malloc((maxlen+1)*sizeof(wchar_t));        // ВЫДЕЛЕННАЯ ПАМЯТЬ UPSTR
        wchar_t* dwStr = malloc((maxlen+1)*sizeof(wchar_t));        // ВЫДЕЛЕННАЯ ПАМЯТЬ DWSTR
        if (i < 1){
            swprintf(befTmp, maxlen, L"%ls", word - i);
            wcsncpy(upStr, mask, wcslen(befTmp));
            wcsncpy(dwStr, befTmp, wcslen(befTmp));
        }
        else{
            swprintf(aftTmp, maxlen, L"%ls", mask + i);
            wcsncpy(upStr, aftTmp, wcslen(aftTmp));
            wcsncpy(dwStr, word, wcslen(aftTmp));
        }

        if (i != 0) lstar_tmp = 1;
        if (i != -word_len + mask_len) rstar_tmp = 1;

        //wprintf(L"\n%ls\n%ls\n", upStr, dwStr);

        wchar_t* tmpMask = malloc((maxlen+3)*sizeof(wchar_t));      // ВЫДЕЛЕННАЯ ПАМЯТЬ TMPMASK
        int congs = 0;
        int symbMarks = (wcslen(dwStr) < wcslen(upStr)) ? wcslen(dwStr) : wcslen(upStr);
        for (int j = 0; j < symbMarks; j++){
            if (upStr[j] == dwStr[j]){
                tmpMask[j] = upStr[j];
                congs++;
            }
            else tmpMask[j] = '?';
            tmpMask[j+1] = 0;
        }

        if (i == 0) wcscpy(emptyMask, tmpMask);

        if (congs >= maxCongs){
            lstar = lstar_tmp;
            rstar = rstar_tmp;
            maxCongs = congs;
            wcscpy(unstarMask, tmpMask);

            free(upStr);
            free(dwStr);
            free(tmpMask);
        }
    }

    if (maxCongs == 0) wcscpy(unstarMask, emptyMask);

    lstar |= lstar_inp;
    rstar |= rstar_inp;
    switch (lstar){
        case 1:
            swprintf(outMask, maxlen+2, L"%c%ls%c", '*', unstarMask, (rstar == 1) ? '*' : ' ');
            break;
        case 0:
            swprintf(outMask, maxlen+2, L"%ls%c", unstarMask, (rstar == 1) ? '*' : ' ');
            break;
    }

    free(emptyMask);
    free(befTmp);
    free(aftTmp);
    free(unstarMask);
    return outMask;
}




int main(){
    wchar_t* input = malloc(100*sizeof(wchar_t));
    wchar_t* buffer;
    wchar_t* del = L" ,\n";
    fgetws(input, 90, stdin);
    wchar_t* mask = wcstok(input, del, &buffer);
    wchar_t* word = wcstok(buffer, del, &buffer);

    mask = getMask(mask, word, 9);
    wprintf(L"%ls\n", mask);
    return 0;
}


























