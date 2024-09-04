#include <cstdio>
#include <iostream>
using namespace std;

int a1[12], a2[12], a3[12];
char einStr[]    = "Enter integer #";
char moStr[]     = "Max of ";
char ieStr[]     = " ints entered...";
char emiStr[]    = "Enter more ints? (n or N = no, others = yes) ";
char begA1Str[]  = "beginning a1: ";
char nn09A1Str[] = "a1 (noneg09): ";
char procA1Str[] = "processed a1: ";
char procA2Str[] = "          a2: ";
char procA3Str[] = "          a3: ";
char dacStr[]    = "Do another case? (n or N = no, others = yes) ";
char dlStr[]     = "================================";
char byeStr[]    = "bye...";

int main() {
    char oneChar;
    int used1, used2, used3, target, oneInt, count, iter;
    int* hopPtr1;
    int* hopPtrX;
    int* hopPtr2;
    int* hopPtr3;
    int* endPtr1;
    int* endPtr2;
    int* endPtr3;

    oneChar = 'y';

start_case:
   if (oneChar == 'n' || oneChar == 'N') goto end_case;
   used1 = 0;
   hopPtr1 = a1;

enter_integers:
   if (oneChar == 'n' || oneChar == 'N') goto process_arrays;
   cout << einStr << (used1 + 1) << ':' << ' ';
   cin >> *hopPtr1;
   ++used1;
   ++hopPtr1;

   if (used1 >= 12) goto max_ints_reached;
   cout << emiStr;
   cin >> oneChar;
   goto enter_integers;

max_ints_reached:
   cout << moStr << 12 << ieStr << endl;
   oneChar = 'n';
   goto process_arrays;

process_arrays:
   cout << endl;
   cout << begA1Str;
   if (used1 <= 0) goto check_used1;

print_begA1:
   hopPtr1 = a1;
   endPtr1 = a1 + used1;

print_begA1_loop:
   if (hopPtr1 >= endPtr1) goto check_used1;
   cout << *hopPtr1 << ' ' << ' ';
   ++hopPtr1;
   goto print_begA1_loop;

check_used1:
   cout << endl;
   if (used1 <= 0) goto copy_arrays;
   hopPtr1 = a1;
   endPtr1 = a1 + used1;

filter_a1_loop_start:
   if (hopPtr1 >= endPtr1) goto filter_a1_loop_end;
   target = *hopPtr1;
   if (target >= 0 && target <= 9) goto filter_a1_continue;
   hopPtrX = hopPtr1 + 1;

shift_left_loop_start:
   if (hopPtrX >= endPtr1) goto shift_left_loop_end;
   *(hopPtrX - 1) = *hopPtrX;
   ++hopPtrX;
   goto shift_left_loop_start;

shift_left_loop_end:
   --used1;
   --endPtr1;
   if (hopPtr1 < endPtr1) goto filter_a1_loop_start;
   goto filter_a1_continue;

filter_a1_continue:
   ++hopPtr1;
   goto filter_a1_loop_start;

filter_a1_loop_end:
   cout << nn09A1Str;
   if (used1 > 0) goto print_nn09A1;
   cout << endl;
   goto copy_arrays;

print_nn09A1:
   hopPtr1 = a1;
   endPtr1 = a1 + used1;

print_nn09A1_loop:
   if (hopPtr1 >= endPtr1) goto copy_arrays;
   cout << *hopPtr1 << ' ' << ' ';
   ++hopPtr1;
   goto print_nn09A1_loop;

copy_arrays:
   used2 = 0;
   used3 = 0;
   hopPtr1 = a1;
   hopPtr2 = a2;
   hopPtr3 = a3;
   endPtr1 = a1 + used1;

copy_array_loops:
   if (hopPtr1 >= endPtr1) goto iter_setup;
   oneInt = *hopPtr1;
   *hopPtr2 = oneInt;
   ++used2;
   ++hopPtr2;
   *hopPtr3 = oneInt;
   ++used3;
   ++hopPtr3;
   ++hopPtr1;
   goto copy_array_loops;

iter_setup:
   iter = 0;
   goto iter_loop_start;

iter_loop_start:
   if (iter >= 3) goto iter_loop_end;
   ++iter;
   count = 0;
   if (iter == 1) goto iter_1_start;
   if (iter == 2) goto iter_2_start;
   goto iter_3_start;

iter_1_start:
   endPtr1 = a1 + used1;
   hopPtr1 = a1;
   goto iter_1_for_loop;

iter_1_for_loop:
   if (hopPtr1 >= endPtr1) goto iter_1_end;
   target = *hopPtr1;
   if (target == 5) goto iter_1_for_loop_continue;
   ++count;
   goto iter_1_for_loop_continue;

iter_1_for_loop_continue:
   ++hopPtr1;
   goto iter_1_for_loop;

iter_1_end:
   used1 -= count;
   if (used1 != 0) goto iter_loop_continue;
   hopPtr1 = a1;
   *hopPtr1 = -101;
   ++used1;
   goto iter_loop_continue;

iter_2_start:
   endPtr2 = a2 + used2;
   hopPtr2 = a2;
   goto iter_2_for_loop;

iter_2_for_loop:
   if (hopPtr2 >= endPtr2) goto iter_2_end;
   target = *hopPtr2;
   if (target <= 4) goto iter_2_for_loop_continue;
   ++count;
   goto iter_2_for_loop_continue;

iter_2_for_loop_continue:
   ++hopPtr2;
   goto iter_2_for_loop;

iter_2_end:
   used2 -= count;
   if (used2 != 0) goto iter_loop_continue;
   hopPtr2 = a2;
   *hopPtr2 = -101;
   ++used2;
   goto iter_loop_continue;

iter_3_start:
   endPtr3 = a3 + used3;
   hopPtr3 = a3;
   goto iter_3_for_loop;

iter_3_for_loop:
   if (hopPtr3 >= endPtr3) goto iter_3_end;
   target = *hopPtr3;
   if (target >= 6) goto iter_3_for_loop_continue;
   ++count;
   goto iter_3_for_loop_continue;

iter_3_for_loop_continue:
   ++hopPtr3;
   goto iter_3_for_loop;

iter_3_end:
   used3 -= count;
   if (used3 != 0) goto iter_loop_continue;
   hopPtr3 = a3;
   *hopPtr3 = -101;
   ++used3;
   goto iter_loop_continue;

iter_loop_continue:
   goto iter_loop_start;

iter_loop_end:
   cout << endl;
   cout << procA1Str;
   if (used1 <= 0) goto print_a2_array;
   hopPtr1 = a1;
   endPtr1 = a1 + used1;
   goto print_a1_array_loop;

print_a1_array_loop:
   if (hopPtr1 >= endPtr1) goto print_a2_array;
   cout << *hopPtr1 << ' ' << ' ';
   ++hopPtr1;
   goto print_a1_array_loop;

print_a2_array:
   cout << endl;
   cout << procA2Str;
   if (used2 <= 0) goto print_a3_array;
   hopPtr2 = a2;
   endPtr2 = a2 + used2;
   goto print_a2_array_loop;

print_a2_array_loop:
   if (hopPtr2 >= endPtr2) goto print_a3_array;
   cout << *hopPtr2 << ' ' << ' ';
   ++hopPtr2;
   goto print_a2_array_loop;

print_a3_array:
   cout << endl;
   cout << procA3Str;

   if (used3 <= 0) goto ask_another_case;
   hopPtr3 = a3;
   endPtr3 = a3 + used3;
   
   goto print_a3_array_loop;

print_a3_array_loop:
   if (hopPtr3 >= endPtr3) goto ask_another_case;
   
   cout << *hopPtr3 << ' ' << ' ';
   ++hopPtr3;
   goto print_a3_array_loop;

ask_another_case:
   cout << endl << dacStr;
   cin >> oneChar;
   
   goto start_case;

end_case:
   cout << endl;
   cout << dlStr << '\n';
   cout << byeStr << '\n';
   cout << dlStr << '\n';

   return 0;
}
