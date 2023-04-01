//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef doctorStrange_h
#define doctorStrange_h

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

///STUDENT'S ANSWER BEGINS HERE
///STUDENTS CAN ADD HELPER FUNCTIONS
struct parameters {
    int HP_int;
    int maxHP;
    int LV_int;
    int EXP_int;
    int TS_int;
    int count;
    int i;
    int cloak;
    bool cloak_real;
    int Wong;
    int count_Wong;
    int poisonous_mushroom;
    bool Wanda_deprive;
    int TS_deprive;
};

int length(string s) {
    int i = 0;
    while (s[i]) {
        i++;
    }
    return i;
}
int find(string s1, string s2) {
    for( int i = 0; i < length(s1); i++) {
        string s = "";
        for (int j = i; j < length(s2) + i; j++) {
            s += s1[j];
        }
        if (s == s2) return i;
    }
    return -1;
}
bool isPrime(int a) {
    if (a == 3) return true;
    int q = sqrt(a);
    for (int i = 2; i <= q; i++) {
        if (a % i == 0) return false;
    }
    return true;
}
int Prime(int HP_int) {
    if (HP_int == 1 || HP_int == 0) return 2;
    else if (!(HP_int & 1)) HP_int++;
    while (!isPrime(HP_int)) {
        HP_int += 2;
    }
    return HP_int;
}
int Fibonaci(int n) {
    int a = 0, b = 1;
    int c;
    while (a + b < n) {
        c = a + b;
        a = b;
        b = c; 
    }
    return b;
}
string reverse(string s) {
    for (int i = 0; i < length(s) / 2; i++) {
        char ch = s[i];
        s[i] = s[length(s) - i - 1];
        s[length(s) - i - 1] = ch;
    }
    return s;
}
string move_string(string s, int ith) {
    for (int i = 0; i < length(s); i++) {
        s[i] += ith;
        if (s[i] > 'z') s[i] -= ('z' - 'a' + 1);
        else if (s[i] > 'Z' && s[i] < 'a') s[i] -= ('Z' - 'A' + 1) ;
    }
    return s;
}

void LV_Up(int & LV_int, int & EXP_int, int & HP_int, int & maxHP) {
    while (EXP_int >= 100) {
        if (LV_int == 10) {
            if (EXP_int > 100) {
                EXP_int = 100;
            }
            break;
        }
        LV_int++;
        HP_int += 10;
        maxHP += 50;
        EXP_int -= 100;
    }
    if (maxHP > 999) maxHP = 999;
    if (HP_int > 999) HP_int = 999;
    return;
}
void LV_Down(int & LV_int) {
    if (LV_int >= 3) {
        LV_int -= 2;
    }
    else {
        LV_int = 1;
    }
    return;
}

void give_poison(int & LV_int,int & poisonous_mushroom) {
    poisonous_mushroom--;
    if (poisonous_mushroom < 0) {
        poisonous_mushroom = 0;
    }
    else if (poisonous_mushroom == 0) {
        LV_int += 2;
    }
    return;
} 


bool use_TS(int & TS_int, int & HP_int, int & maxHP) {
    if (TS_int > 0) {
        TS_int--;
        HP_int = maxHP;
        return true;
    }
    return false;
}
void use_cloak(int & cloak, int & G, int & LV_int, int HP_int, int count , bool win, bool cloak_real, bool Wanda_deprive) {
    if (cloak_real && !Wanda_deprive) {
        if (win && cloak > 0) {
            int y = Prime(HP_int);
            G = (count + y) % 100;
        } 
        if (!win && cloak > 0) {
            int y = Prime(HP_int);
            G = (count + y) % 100;
            cloak--;   
            if (cloak == 0) {
                LV_Down(LV_int);
            }
        }
        else {
            G = 0;
        }
    }
    return;
}
int handleEvents(string & HP, string & LV, string & EXP, string & TS, string & events) {
    ///Students have to complete this function and DO NOT modify any parameters in this function.
    int result = 0;
    int maxHP = stoi(HP), HP_int = stoi(HP), LV_int = stoi(LV), EXP_int = stoi(EXP), TS_int = stoi(TS);
    int count = 1, index = 0, G = 0, cloak = 0,count_Wong = 0, poisonous_mushroom = 0, TS_deprive = 0;
    int Wong[100];
    for (int i = 0; i < 100; i++) {
        Wong[i] = 0;
    }
    bool check_die = false, cloak_real = false, Wanda_deprive = false, check15 = false;
    parameters Dr[100];
    for (int i = 1; i < length(events); i++) {
        if (events[i] == '!') {
            index = i;
            break;
        }
    }
    if (events[0] != '!' || !index) return HP_int + LV_int + EXP_int + TS_int;
    for (int i = 1; i < index; i++) {
        Dr[count] = {HP_int, maxHP, LV_int, EXP_int, TS_int, count, i, cloak, cloak_real, Wong[count_Wong], count_Wong, poisonous_mushroom, Wanda_deprive, TS_deprive};
        string numstr = "";
        while (events[i] != '#' && events[i] != ' ') {
            numstr += events[i];
            i++;
        }

        if (stoi(numstr) >= 1 && stoi(numstr) <= 5) {
            int b = count % 10;
            int LV0 = count > 6 ? (b > 5 ? b : 5) : b;
            if (LV_int >= 7 && count_Wong >= 1) {
                Wong[count_Wong] = 0;
            }
            if (Wong[0]) {
                if (stoi(numstr) == 1) EXP_int += 10;
                else if (stoi(numstr) == 2) EXP_int += 20;
                else if (stoi(numstr) == 3) EXP_int += 40;
                else if (stoi(numstr) == 4) EXP_int += 50;
                else if (stoi(numstr) == 5) EXP_int += 70;
                LV_Up(LV_int,EXP_int,HP_int,maxHP);
                Wong[0] -= 1;
            }
            else if (Wong[count_Wong]) {
                use_cloak(cloak,G,LV_int, HP_int, count, false, cloak_real, Wanda_deprive);
                if (stoi(numstr) == 1) HP_int -= 1.5*LV0*10*(100 - G)/100;
                else if (stoi(numstr) == 2) HP_int -= 2.5*LV0*10*(100 - G)/100;
                else if (stoi(numstr) == 3) HP_int -= 4.5*LV0*10*(100 - G)/100;
                else if (stoi(numstr) == 4) HP_int -= 7.5*LV0*10*(100 - G)/100;
                else if (stoi(numstr) == 5) HP_int -= 9.5*LV0*10*(100 - G)/100;
                Wong[count_Wong] -= 1;
                if (HP_int <= 0 && TS_int > 0) {
                    Wong[count_Wong] = 0;
                }
                if (HP_int <= 0) {
                    if (!use_TS(TS_int,HP_int,maxHP)) {
                        check_die = true;
                        break;
                    }
                }
            }
            else if (LV_int > LV0) {
                if (stoi(numstr) == 1) EXP_int += 10;
                else if (stoi(numstr) == 2) EXP_int += 20;
                else if (stoi(numstr) == 3) EXP_int += 40;
                else if (stoi(numstr) == 4) EXP_int += 50;
                else EXP_int += 70;
                LV_Up(LV_int,EXP_int,HP_int,maxHP);
            }
            else if (LV_int == LV0) {
                if (stoi(numstr) == 1) EXP_int += 10/2;
                else if (stoi(numstr) == 2) EXP_int += 20/2;
                else if (stoi(numstr) == 3) EXP_int += 40/2;
                else if (stoi(numstr) == 4) EXP_int += 50/2;
                else EXP_int += 70/2;
                LV_Up(LV_int,EXP_int,HP_int,maxHP);
            }
            else {
                use_cloak(cloak,G,LV_int, HP_int, count, false, cloak_real, Wanda_deprive);
                if (stoi(numstr) == 1) HP_int -= 1.5*LV0*10*(100 - G)/100;
                else if (stoi(numstr) == 2) HP_int -= 2.5*LV0*10*(100 - G)/100;
                else if (stoi(numstr) == 3) HP_int -= 4.5*LV0*10*(100 - G)/100;
                else if (stoi(numstr) == 4) HP_int -= 7.5*LV0*10*(100 - G)/100;
                else HP_int -= 9.5*LV0*10*(100 - G)/100;
                if (HP_int <= 0) {
                    if (!use_TS(TS_int,HP_int,maxHP)) {
                        check_die = true;
                        break;
                    }
                }
            } 
        }
        else if (stoi(numstr) == 6) {
            string mantra = "";
            i++;
            while (events[i] != '#' && events[i] != '!') {
                mantra += events[i];
                i++;
            }
            int ata = 0, def = 0;
            for (int a = 0; a < length(mantra); a++) {
                if (mantra[a] == 'a' || mantra[a] == 'A') {
                    for (int b = a + 1; b < length(mantra); b++) {
                        if (mantra[b] == 't' || mantra[b] == 'T') {
                            for (int c = b + 1; c < length(mantra); c++) {
                                if (mantra[c] == 't' || mantra[c] == 'T') {
                                    for (int d = c + 1; d < length(mantra); d++) {
                                        if (mantra[d] == 'a' || mantra[d] == 'A') {
                                            for (int e = d + 1; e < length(mantra); e++) {
                                                if (mantra[e] == 'c' || mantra[e] == 'C') {
                                                    for (int f = e + 1; f < length(mantra); f++) {
                                                        if (mantra[f] == 'k' || mantra[f] == 'K') ata++;
                                                        break;
                                                    }
                                                    break;
                                                }
                                            }
                                            break;
                                        }
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }
            }
            for (int a = 0; a < length(mantra); a++) {
                if (mantra[a] == 'd' || mantra[a] == 'D') {
                    for (int b = a + 1; b < length(mantra); b++) {
                        if (mantra[b] == 'e' || mantra[b] == 'E') {
                            for (int c = b + 1; c < length(mantra); c++) {
                                if (mantra[c] == 'f' || mantra[c] == 'F') {
                                    for (int d = c + 1; d < length(mantra); d++) {
                                        if (mantra[d] == 'e' || mantra[d] == 'E') {
                                            for (int e = d + 1; e < length(mantra); e++) {
                                                if (mantra[e] == 'n' || mantra[e] == 'N') {
                                                    for (int f = e + 1; f < length(mantra); f++) {
                                                        if (mantra[f] == 's' || mantra[f] == 'S') {
                                                            for (int g = f + 1; g < length(mantra); g++) {
                                                                if (mantra[g] == 'e' || mantra[f] == 'E') def++;
                                                            }
                                                        }
                                                        break;
                                                    }
                                                    break;
                                                }
                                            }
                                            break;
                                        }
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }
            }
            int F = (count + length(mantra)) % 100;
            use_cloak(cloak,G, LV_int,HP_int, count, true, cloak_real, Wanda_deprive);
            if (ata*10 + G > F) {
                EXP_int += 200;
                TS_int++;
                LV_Up(LV_int,EXP_int,HP_int,maxHP);
            }
            else {
                use_cloak(cloak,G, LV_int,HP_int, count , false, cloak_real, Wanda_deprive);
                if (def*10 + G < 100) {
                    HP_int = HP_int - HP_int*(100 - def*10 - G)/100;
                }
                if (!use_TS(TS_int,HP_int,maxHP) && HP_int <= 0) {
                    check_die = true;
                    break;
                }
            }
        }
        else if (stoi(numstr) == 7 && !cloak_real) {
            cloak += 3;
            LV_int += 2;
            cloak_real = true;
            if (Wong[count_Wong] && count_Wong) {
                Wong[count_Wong] = 0;
            }
        }
        else if (stoi(numstr) == 8) {
            if (count_Wong == 0) {
                Wong[count_Wong] = 3;
            }
            else {
                Wong[count_Wong] = 3;
                if (Wong[0] != 0) {
                    Wong[count_Wong] = 0;
                    Wong[0]--;
                }
                else if (count_Wong >= 2) {
                    Wong[count_Wong - 1] = 0;
                }
            }
            if (Wong[count_Wong] && count_Wong) {
                cloak_real = false;
            }
            count_Wong++;
        }
        else if (stoi(numstr) == 9) {
            HP_int = maxHP;
            if (count_Wong >= 1) {
                Wong[count_Wong] = 0;
            }
            cloak_real = true;
            cloak = 3;
        }
        else if (stoi(numstr) == 10) {
            HP_int += Fibonaci(HP_int);
            if (HP_int > maxHP) HP_int = maxHP;
        }
        else if (stoi(numstr) == 11) {
            if (Wong[0]) {
                Wong[0]--;
            }
            else {
                HP_int -= 50;
                if (Wong[count_Wong] && count_Wong) {
                    Wong[count_Wong]--;
                }
                if (HP_int <= 0) {
                    if (use_TS(TS_int,HP_int,maxHP)) {
                        if (count_Wong && Wong[count_Wong]) {
                            Wong[count_Wong] = 0;
                        }
                    }
                    else {
                        check_die = true;
                        break;
                    }
                }
                if (!poisonous_mushroom) {
                    LV_int -= 2;
                    if (LV_int < 1) LV_int = 1;
                    poisonous_mushroom = 4;
                }
            }
        }
        else if (stoi(numstr) == 12) {
            string code_snippet1 = "", code_snippet2 = "";
            string mid = "";
            i++;
            while (events[i] != ' ') {
                code_snippet1 += events[i];
                i++;
            }
            i++;
            while (events[i] != '#' && events[i] != '!') {
                code_snippet2 += events[i];
                i++;
            }
            string l_code1 = "", r_code1 = "";
            for (int j = 0; j < length(code_snippet1) / 2; j++) {
                l_code1 += code_snippet1[j];
            }
            mid += code_snippet1[length(code_snippet1) / 2];
            for (int j = length(code_snippet1) / 2 + 1; j < length(code_snippet1); j++) {
                r_code1 += code_snippet1[j];
            }
            code_snippet1 = "";
            code_snippet1 =  reverse(l_code1) + mid + reverse(r_code1);
            int ith = length(code_snippet2) % 10;
            code_snippet1 = move_string(code_snippet1, ith);
            if (find(code_snippet1,code_snippet2) < length(code_snippet1)) {
                HP_int -= HP_int*10/100;
                maxHP -= maxHP*10/100;
                EXP_int += 30;
                LV_Up(LV_int,EXP_int,HP_int,maxHP);
            }
            else {
                Wanda_deprive = true;
                TS_deprive = TS_int;
                TS_int = 0;
                EXP_int += 15;
                LV_Up(LV_int,EXP_int,HP_int,maxHP);
            }
        }
        else if (stoi(numstr) == 13) {
            int arr[7][7], row = 0, col = 0;
            string num = "";
            int m = (count % 7) > 2 ? (count % 7) : 2;
            i++;
            while (events[i] != '#' && events[i] != '!' && i < index) {
                while (events[i] != ' '  && events[i] != '#' && events[i] != '!' && i < index) {
                    num += events[i];
                    i++;
                }
                arr[row][col++] = stoi(num);
                if (col == 7) {
                    row++;
                    col = 0;
                }
                num = "";
                i++;
            }
            int min_row = 0, min_col = 0;
            int min = 0;
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < m; k++) {
                    min += arr[j][k];
                }
            }
            for (int j = 0; j < 7 - m + 1; j++) {
                for (int k = 0; k < 7 - m + 1; k++) {
                    int temp = 0;
                    for (int a = 0; a < m; a++) {
                        for (int b = 0; b < m; b++) {
                            temp += arr[j + a][k + b];
                        }
                    }
                    if (temp < min) {
                                min = temp;
                                min_row = j;
                                min_col = k;
                    } 
                }
            }
            bool increasing = true;
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < m - 1; k++) {
                    if (arr[k + min_row][j + min_col] > arr[k + min_row + 1][j + min_col]) {
                        increasing = false;
                        break;
                    }
                }
            }
            if (increasing) {
                HP_int += min*(min_col + min_row + 2);
                if (HP_int > maxHP) HP_int = maxHP;
            }
            else {
                HP_int -= min*(min_col + min_row + 2);
                if (!Wanda_deprive && HP_int <= 0) {
                    HP = 1;
                }
                else if (HP_int <= 0 && use_TS(TS_int,HP_int,maxHP)) {
                    check_die = true;
                    break;
                } 
            }
            // cout<<min<<" "<<min_col<<" "<<min_row<<endl;
        }
        else if (stoi(numstr) == 14) {
            int arr[1000];
            int count_arr = 0;
            int sr;
            string sr_str = "";
            i++;
            while (events[i] != ' ') {
                sr_str += events[i];
                i++;
            }
            sr = stoi(sr_str);
            sr_str = "";
            while (events[i] != '#' && events[i] != '!' && i < index) {
                i++;
                while (events[i] != ' ' && events[i] != '#' && events[i] != '!' && i < index) {
                    sr_str += events[i];
                    i++;
                }
                arr[count_arr++] = stoi(sr_str);
                sr_str = "";
            }
            // cout<<sr<<" ";
            // for (int j = 0; j < count_arr; j++) {
            //     cout<<arr[j]<<" ";
            // }
            int l = 0, r = count_arr - 1;
            int count_sr = 0;
            bool find_ = false;
            while (r > l) {
                count_sr++;
                int mid = (r + l) / 2;
                if (arr[mid] > sr) {
                    l = mid + 1;
                }
                else {
                    r = mid;
                }
                if (arr[mid] == sr) {
                    find_ = true;
                    break;
                }
            }
            cout<<count_sr;
            if (find_) {
                LV_int = 1;
                HP_int -= (int)(count_sr)*(count % 10)*7;
            }
            else {
                EXP_int += 150;
                LV_Up(LV_int,EXP_int,HP_int,maxHP);
                Wanda_deprive = false;
                TS_int += TS_deprive;
            }
        }
        else if (stoi(numstr) == 15 && !check15 && TS_int > 0) {
            parameters max = Dr[count];
            for (int j = count - 1; j >= 1; j--) {
                if (max.HP_int < Dr[j].HP_int) max = Dr[j];
            }
            HP_int = max.HP_int;
            maxHP = max.maxHP;
            LV_int = 10;
            EXP_int = 100;
            count = max.count;
            TS_int--;
            i = max.i - 1;
            cloak = max.cloak;
            cloak_real = max.cloak_real;
            count_Wong = max.count_Wong;
            Wong[count_Wong] = max.Wong;
            poisonous_mushroom = max.poisonous_mushroom;
            Wanda_deprive = max.Wanda_deprive;
            TS_deprive = max.TS_deprive;
            check15 = true;
        }
        give_poison(LV_int, poisonous_mushroom);
        count++;
    }
    HP= to_string(HP_int);
    LV  = to_string(LV_int);
    EXP= to_string(EXP_int);
    TS= to_string(TS_int);
    if (check_die) result = -1;
    else result =  HP_int + LV_int + EXP_int + TS_int;
    // cout << HP << " " << LV << " " << EXP << " " << TS << endl;
    // cout << events << endl;
    return result;
}

///END OF STUDENT'S ANSWER

#endif /* studyInPink_h */
