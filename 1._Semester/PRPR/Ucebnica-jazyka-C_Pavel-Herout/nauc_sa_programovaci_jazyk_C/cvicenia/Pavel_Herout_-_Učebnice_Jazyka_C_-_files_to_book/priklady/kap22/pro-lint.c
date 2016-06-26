main()
{
  int i, j;
  char c;

  while ((c = getchar()) != 'Z') {
    putchar(c);
    i++;
  }
  printf("Zpracovano %d znaku\n", i);
}

