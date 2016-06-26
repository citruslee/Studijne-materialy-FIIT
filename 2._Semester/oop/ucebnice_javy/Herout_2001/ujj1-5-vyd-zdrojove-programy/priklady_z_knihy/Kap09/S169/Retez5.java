/////////////////////////////////////////////////////////////////
//                                                             //
// Tento zdrojový kód je souèástí distribuce balíku programù,  //
//     poskytovaných jako doplòující informace ke knize        //
//                                                             //
//                  Uèebnice jazyka Java                       //
//                                                             //
//     Pøeètìte si, prosím, dùkladnì upozornìní v souboru      // 
//                       CTI_ME.TXT                            //
//        který je nedílnou souèástí této distribuce           //
//                                                             //
//                 (c) Pavel Herout, 2000                      // 
//                                                             //
/////////////////////////////////////////////////////////////////

public class Retez5 {
  public static void main(String[] args) {
    String s1 = "mala a";
    String s2 = " VELKA";
    String s3, s4;

    s3 = s1 + s2;
    s4 = s1.concat(s2);
    System.out.println(s1);  // "mala a"
    System.out.println(s2);  // " VELKA"
    System.out.println(s3);  // "mala a VELKA"
    System.out.println(s4);  // "mala a VELKA"
  }
}
