xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 98;
 0.00000;6.65450;0.00000;,
 17.39909;6.65450;-17.39909;,
 0.00000;6.65450;-24.60603;,
 24.60603;6.65450;0.00000;,
 17.39909;6.65450;17.39909;,
 -0.00000;6.65450;24.60603;,
 -17.39910;6.65450;17.39909;,
 -24.60603;6.65450;-0.00000;,
 -17.39909;6.65450;-17.39909;,
 20.95858;67.21285;-20.95858;,
 0.00000;67.21285;-29.63991;,
 29.63991;67.21285;0.00000;,
 20.95858;67.21285;20.95858;,
 -0.00000;67.21285;29.63991;,
 -20.95858;67.21285;20.95858;,
 -29.63991;67.21285;-0.00000;,
 -20.95858;67.21285;-20.95858;,
 22.51001;65.74684;-22.51001;,
 0.00000;65.74684;-31.83397;,
 31.83397;65.74684;0.00000;,
 22.51001;65.74684;22.51001;,
 -0.00000;65.74684;31.83397;,
 -22.51001;65.74684;22.51001;,
 -31.83397;65.74684;-0.00000;,
 -22.51001;65.74684;-22.51001;,
 23.54666;63.55278;-23.54665;,
 0.00000;63.55278;-33.29999;,
 33.29999;63.55278;0.00000;,
 23.54665;63.55278;23.54665;,
 -0.00000;63.55278;33.29999;,
 -23.54666;63.55278;23.54665;,
 -33.29999;63.55278;-0.00000;,
 -23.54666;63.55278;-23.54665;,
 23.91067;60.96472;-23.91067;,
 0.00000;60.96472;-33.81480;,
 33.81480;60.96472;0.00000;,
 23.91067;60.96472;23.91067;,
 -0.00000;60.96472;33.81480;,
 -23.91068;60.96472;23.91066;,
 -33.81480;60.96472;-0.00000;,
 -23.91067;60.96472;-23.91066;,
 23.91067;42.93014;-23.91067;,
 0.00000;42.93014;-33.81480;,
 33.81480;42.93014;0.00000;,
 23.91067;42.93014;23.91067;,
 -0.00000;42.93014;33.81480;,
 -23.91068;42.93014;23.91066;,
 -33.81480;42.93014;-0.00000;,
 -23.91067;42.93014;-23.91066;,
 23.32177;24.89559;-23.32177;,
 0.00000;24.89559;-32.98196;,
 32.98196;24.89559;0.00000;,
 23.32177;24.89559;23.32177;,
 -0.00000;24.89559;32.98196;,
 -23.32177;24.89559;23.32176;,
 -32.98196;24.89559;-0.00000;,
 -23.32177;24.89559;-23.32176;,
 21.74887;6.56000;-21.74887;,
 0.00000;6.56000;-30.75753;,
 30.75753;6.56000;0.00000;,
 21.74887;6.56000;21.74887;,
 -0.00000;6.56000;30.75753;,
 -21.74887;6.56000;21.74886;,
 -30.75753;6.56000;-0.00000;,
 -21.74887;6.56000;-21.74886;,
 21.41776;4.20592;-21.41776;,
 0.00000;4.20592;-30.28928;,
 30.28928;4.20592;0.00000;,
 21.41776;4.20592;21.41776;,
 -0.00000;4.20592;30.28928;,
 -21.41776;4.20592;21.41775;,
 -30.28928;4.20592;-0.00000;,
 -21.41776;4.20592;-21.41775;,
 20.47484;2.21023;-20.47484;,
 0.00000;2.21023;-28.95580;,
 28.95580;2.21023;0.00000;,
 20.47484;2.21023;20.47484;,
 -0.00000;2.21023;28.95580;,
 -20.47484;2.21023;20.47484;,
 -28.95580;2.21023;-0.00000;,
 -20.47484;2.21023;-20.47484;,
 19.06368;0.87675;-19.06368;,
 0.00000;0.87675;-26.96012;,
 26.96012;0.87675;0.00000;,
 19.06368;0.87675;19.06368;,
 -0.00000;0.87675;26.96012;,
 -19.06368;0.87675;19.06368;,
 -26.96012;0.87675;-0.00000;,
 -19.06368;0.87675;-19.06368;,
 17.39909;0.40850;-17.39909;,
 0.00000;0.40850;-24.60603;,
 24.60603;0.40850;0.00000;,
 17.39909;0.40850;17.39909;,
 -0.00000;0.40850;24.60603;,
 -17.39910;0.40850;17.39909;,
 -24.60603;0.40850;-0.00000;,
 -17.39909;0.40850;-17.39909;,
 0.00000;0.40850;0.00000;;
 
 104;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,2,8;,
 4;2,1,9,10;,
 4;1,3,11,9;,
 4;3,4,12,11;,
 4;4,5,13,12;,
 4;5,6,14,13;,
 4;6,7,15,14;,
 4;7,8,16,15;,
 4;8,2,10,16;,
 4;10,9,17,18;,
 4;9,11,19,17;,
 4;11,12,20,19;,
 4;12,13,21,20;,
 4;13,14,22,21;,
 4;14,15,23,22;,
 4;15,16,24,23;,
 4;16,10,18,24;,
 4;18,17,25,26;,
 4;17,19,27,25;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,24,32,31;,
 4;24,18,26,32;,
 4;26,25,33,34;,
 4;25,27,35,33;,
 4;27,28,36,35;,
 4;28,29,37,36;,
 4;29,30,38,37;,
 4;30,31,39,38;,
 4;31,32,40,39;,
 4;32,26,34,40;,
 4;34,33,41,42;,
 4;33,35,43,41;,
 4;35,36,44,43;,
 4;36,37,45,44;,
 4;37,38,46,45;,
 4;38,39,47,46;,
 4;39,40,48,47;,
 4;40,34,42,48;,
 4;42,41,49,50;,
 4;41,43,51,49;,
 4;43,44,52,51;,
 4;44,45,53,52;,
 4;45,46,54,53;,
 4;46,47,55,54;,
 4;47,48,56,55;,
 4;48,42,50,56;,
 4;50,49,57,58;,
 4;49,51,59,57;,
 4;51,52,60,59;,
 4;52,53,61,60;,
 4;53,54,62,61;,
 4;54,55,63,62;,
 4;55,56,64,63;,
 4;56,50,58,64;,
 4;58,57,65,66;,
 4;57,59,67,65;,
 4;59,60,68,67;,
 4;60,61,69,68;,
 4;61,62,70,69;,
 4;62,63,71,70;,
 4;63,64,72,71;,
 4;64,58,66,72;,
 4;66,65,73,74;,
 4;65,67,75,73;,
 4;67,68,76,75;,
 4;68,69,77,76;,
 4;69,70,78,77;,
 4;70,71,79,78;,
 4;71,72,80,79;,
 4;72,66,74,80;,
 4;74,73,81,82;,
 4;73,75,83,81;,
 4;75,76,84,83;,
 4;76,77,85,84;,
 4;77,78,86,85;,
 4;78,79,87,86;,
 4;79,80,88,87;,
 4;80,74,82,88;,
 4;82,81,89,90;,
 4;81,83,91,89;,
 4;83,84,92,91;,
 4;84,85,93,92;,
 4;85,86,94,93;,
 4;86,87,95,94;,
 4;87,88,96,95;,
 4;88,82,90,96;,
 3;90,89,97;,
 3;89,91,97;,
 3;91,92,97;,
 3;92,93,97;,
 3;93,94,97;,
 3;94,95,97;,
 3;95,96,97;,
 3;96,90,97;;
 
 MeshMaterialList {
  1;
  104;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  98;
  0.000000;1.000000;0.000000;,
  0.000000;0.082839;0.996563;,
  -0.704676;0.082839;0.704676;,
  -0.996563;0.082839;-0.000000;,
  -0.704676;0.082839;-0.704676;,
  0.000000;0.082839;-0.996563;,
  0.704677;0.082839;-0.704676;,
  0.996563;0.082839;0.000000;,
  0.704676;0.082839;0.704676;,
  -0.000000;0.709232;-0.704975;,
  0.498493;0.709232;-0.498493;,
  0.704975;0.709232;0.000000;,
  0.498493;0.709232;0.498493;,
  -0.000000;0.709232;0.704975;,
  -0.498493;0.709232;0.498493;,
  -0.704975;0.709232;-0.000000;,
  -0.498493;0.709232;-0.498493;,
  -0.000000;0.384552;-0.923104;,
  0.652733;0.384552;-0.652733;,
  0.923104;0.384552;0.000000;,
  0.652733;0.384552;0.652733;,
  -0.000000;0.384552;0.923104;,
  -0.652733;0.384552;0.652733;,
  -0.923103;0.384552;-0.000000;,
  -0.652733;0.384552;-0.652733;,
  -0.000000;0.098154;-0.995171;,
  0.703692;0.098154;-0.703692;,
  0.995171;0.098154;0.000000;,
  0.703692;0.098155;0.703692;,
  -0.000000;0.098154;0.995171;,
  -0.703692;0.098154;0.703692;,
  -0.995171;0.098154;-0.000000;,
  -0.703692;0.098154;-0.703692;,
  -0.000000;-0.023073;-0.999734;,
  0.706919;-0.023073;-0.706918;,
  0.999734;-0.023073;0.000000;,
  0.706918;-0.023073;0.706919;,
  -0.000000;-0.023073;0.999734;,
  -0.706919;-0.023073;0.706918;,
  -0.999734;-0.023073;-0.000000;,
  -0.706919;-0.023073;-0.706918;,
  -0.000000;-0.083357;-0.996520;,
  0.704646;-0.083357;-0.704646;,
  0.996520;-0.083357;0.000000;,
  0.704646;-0.083357;0.704646;,
  -0.000000;-0.083357;0.996520;,
  -0.704646;-0.083357;0.704646;,
  -0.996520;-0.083357;-0.000000;,
  -0.704646;-0.083357;-0.704646;,
  -0.000000;-0.157907;-0.987454;,
  0.698235;-0.157907;-0.698235;,
  0.987454;-0.157908;0.000000;,
  0.698235;-0.157908;0.698235;,
  -0.000000;-0.157908;0.987454;,
  -0.698235;-0.157907;0.698235;,
  -0.987454;-0.157907;-0.000000;,
  -0.698235;-0.157907;-0.698235;,
  -0.000000;-0.384552;-0.923103;,
  0.652733;-0.384552;-0.652732;,
  0.923103;-0.384552;0.000000;,
  0.652732;-0.384552;0.652733;,
  -0.000000;-0.384552;0.923103;,
  -0.652733;-0.384552;0.652732;,
  -0.923103;-0.384552;-0.000000;,
  -0.652733;-0.384552;-0.652733;,
  0.000000;-0.709230;-0.704977;,
  0.498494;-0.709230;-0.498494;,
  0.704977;-0.709230;0.000000;,
  0.498494;-0.709230;0.498494;,
  -0.000000;-0.709230;0.704977;,
  -0.498494;-0.709230;0.498494;,
  -0.704977;-0.709230;0.000000;,
  -0.498494;-0.709230;-0.498494;,
  0.000000;-0.924735;-0.380611;,
  0.269133;-0.924735;-0.269133;,
  0.380612;-0.924735;0.000000;,
  0.269133;-0.924735;0.269133;,
  0.000000;-0.924735;0.380611;,
  -0.269133;-0.924735;0.269133;,
  -0.380611;-0.924735;0.000000;,
  -0.269133;-0.924735;-0.269133;,
  0.000000;-0.995201;-0.097856;,
  0.069195;-0.995201;-0.069195;,
  0.097856;-0.995201;0.000000;,
  0.069195;-0.995201;0.069195;,
  -0.000000;-0.995201;0.097856;,
  -0.069195;-0.995201;0.069195;,
  -0.097856;-0.995201;0.000000;,
  -0.069195;-0.995201;-0.069195;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;0.831471;-0.555568;,
  0.392846;0.831471;-0.392846;,
  0.555568;0.831471;0.000000;,
  0.392846;0.831471;0.392846;,
  -0.000000;0.831471;0.555568;,
  -0.392846;0.831471;0.392846;,
  -0.555568;0.831471;0.000000;,
  -0.392846;0.831471;-0.392846;;
  104;
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,1,1,8;,
  4;90,91,10,9;,
  4;91,92,11,10;,
  4;92,93,12,11;,
  4;93,94,13,12;,
  4;94,95,14,13;,
  4;95,96,15,14;,
  4;96,97,16,15;,
  4;97,90,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  4;49,50,58,57;,
  4;50,51,59,58;,
  4;51,52,60,59;,
  4;52,53,61,60;,
  4;53,54,62,61;,
  4;54,55,63,62;,
  4;55,56,64,63;,
  4;56,49,57,64;,
  4;57,58,66,65;,
  4;58,59,67,66;,
  4;59,60,68,67;,
  4;60,61,69,68;,
  4;61,62,70,69;,
  4;62,63,71,70;,
  4;63,64,72,71;,
  4;64,57,65,72;,
  4;65,66,74,73;,
  4;66,67,75,74;,
  4;67,68,76,75;,
  4;68,69,77,76;,
  4;69,70,78,77;,
  4;70,71,79,78;,
  4;71,72,80,79;,
  4;72,65,73,80;,
  4;73,74,82,81;,
  4;74,75,83,82;,
  4;75,76,84,83;,
  4;76,77,85,84;,
  4;77,78,86,85;,
  4;78,79,87,86;,
  4;79,80,88,87;,
  4;80,73,81,88;,
  3;81,82,89;,
  3;82,83,89;,
  3;83,84,89;,
  3;84,85,89;,
  3;85,86,89;,
  3;86,87,89;,
  3;87,88,89;,
  3;88,81,89;;
 }
 MeshTextureCoords {
  98;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}