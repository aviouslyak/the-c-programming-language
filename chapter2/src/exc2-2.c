/* Exercise 2-2. Write a loop equivalent to the for loop above without using && or ||. */

// i < lim - 1 && (c = getchar()) != '\n' && c != EOF
/* while (i < lim - 1) {
       c = getchar(); 
      if (c == EOF) {
              break;
      } else if (c == '\n') {
              break; 
      }
}
