/*
 * s408b.c    v.2.0
 *
 * Implicitni int
 * ==============
 */

main(void)
{
  int i = secti(1, 2);
  printf("%d\n", i);

  return 0;
}

secti(int a, int b)
{
  return a + b;
}


