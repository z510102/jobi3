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
 174;
 9.99586;7.46776;-5.73045;,
 0.07805;4.69574;-5.73045;,
 0.07805;4.69574;5.82298;,
 9.99586;7.46772;5.82298;,
 0.07805;-5.73246;-5.73045;,
 0.07805;-5.73246;5.82298;,
 9.99586;-5.81884;-5.73045;,
 9.99586;-5.81884;5.82298;,
 14.31872;-0.51836;-5.73045;,
 14.31872;-0.51836;5.82298;,
 7.25464;-0.51836;-5.73045;,
 14.31872;-0.51836;-5.73045;,
 7.25464;-0.51836;-5.73045;,
 7.25464;-0.51836;-5.73045;,
 7.25464;-0.51836;-5.73045;,
 7.25464;-0.51836;-5.73045;,
 7.25464;-0.51836;5.82298;,
 14.31872;-0.51836;5.82298;,
 7.25464;-0.51836;5.82298;,
 7.25464;-0.51836;5.82298;,
 7.25464;-0.51836;5.82298;,
 7.25464;-0.51836;5.82298;,
 5.08674;0.17304;-5.74629;,
 2.99784;-0.42596;-5.74629;,
 1.61099;5.09980;-5.74629;,
 3.69989;5.69879;-5.74629;,
 5.08674;0.17304;5.83880;,
 3.69989;5.69879;5.83880;,
 1.61099;5.09980;5.83880;,
 2.99784;-0.42596;5.83880;,
 11.73443;-3.64771;-5.74629;,
 10.35218;-5.32450;-5.74629;,
 6.07944;-1.55617;-5.74629;,
 7.46170;0.12066;-5.74629;,
 11.73443;-3.64771;5.83880;,
 7.46170;0.12066;5.83880;,
 6.07944;-1.55617;5.83880;,
 10.35218;-5.32450;5.83880;,
 0.28956;8.05161;6.27171;,
 0.28956;8.05161;-6.17920;,
 0.84567;5.82119;-6.17920;,
 0.84567;5.82119;6.27171;,
 0.28956;8.05161;-6.17920;,
 11.02183;10.72746;-6.17920;,
 11.57794;8.49709;-6.17920;,
 0.84567;5.82119;-6.17920;,
 11.02183;10.72746;6.27171;,
 0.28956;8.05161;6.27171;,
 0.84567;5.82119;6.27171;,
 11.57794;8.49709;6.27171;,
 0.28956;8.05161;-6.17920;,
 0.28956;8.05161;6.27171;,
 11.01014;10.70934;-6.17920;,
 19.69927;-4.14533;-6.17920;,
 17.87556;-5.54472;-6.17920;,
 9.18648;9.31003;-6.17920;,
 19.69927;-4.14533;-6.17920;,
 19.69927;-4.14533;6.27171;,
 17.87556;-5.54472;6.27171;,
 17.87556;-5.54472;-6.17920;,
 19.69927;-4.14533;6.27171;,
 11.01014;10.70934;6.27171;,
 9.18648;9.31003;6.27171;,
 17.87556;-5.54472;6.27171;,
 11.01014;10.70934;-6.17920;,
 11.01014;10.70934;6.27171;,
 9.18648;9.31003;6.27171;,
 9.18648;9.31003;-6.17920;,
 -0.26572;8.30566;1.83543;,
 -0.26572;8.30566;-1.74292;,
 1.58679;3.24900;-1.74292;,
 1.58679;3.24900;1.83543;,
 -0.26572;8.30566;-1.74292;,
 1.44924;8.38882;-1.74292;,
 3.30172;3.92986;-1.74292;,
 1.58679;3.24900;-1.74292;,
 1.44924;8.38882;1.83543;,
 -0.26572;8.30566;1.83543;,
 1.58679;3.24900;1.83543;,
 3.30172;3.92986;1.83543;,
 -0.26572;8.30566;-1.74292;,
 -0.26572;8.30566;1.83543;,
 12.87902;7.17298;-6.17920;,
 13.68220;19.99894;-4.59220;,
 15.97380;17.69400;-4.59220;,
 15.17060;7.35332;-6.14823;,
 13.68220;19.99894;-4.59220;,
 13.68220;19.99894;4.68471;,
 15.97380;17.69400;4.68471;,
 15.97380;17.69400;-4.59220;,
 13.68220;19.99894;4.68471;,
 12.87902;7.17298;6.27171;,
 15.17060;7.35332;6.24074;,
 15.97380;17.69400;4.68471;,
 12.87902;7.17298;-6.17920;,
 12.87902;7.17298;6.27171;,
 15.17060;7.35332;6.24074;,
 15.17060;7.35332;-6.14823;,
 18.65142;-1.89716;6.27171;,
 18.65142;-1.89716;-6.17920;,
 19.40305;1.18256;-6.17920;,
 19.40305;1.18256;6.27171;,
 18.65142;-1.89716;-6.17920;,
 12.95473;7.58380;-6.17920;,
 14.92507;8.76770;-6.02586;,
 19.40305;1.18256;-6.17920;,
 12.95473;7.58380;6.27171;,
 18.65142;-1.89716;6.27171;,
 19.40305;1.18256;6.27171;,
 14.92507;8.76770;6.11837;,
 19.40305;1.18256;6.27171;,
 19.40305;1.18256;-6.17920;,
 19.45164;1.50236;-1.74292;,
 19.45164;1.50236;1.83543;,
 19.73897;-4.15927;1.83543;,
 19.73897;-4.15927;-1.74292;,
 19.45164;1.50236;1.83543;,
 18.32457;1.06596;1.83543;,
 17.89866;-5.55060;1.83543;,
 19.73897;-4.15927;1.83543;,
 18.32457;1.06596;-1.74292;,
 19.45164;1.50236;-1.74292;,
 19.73897;-4.15927;-1.74292;,
 17.89866;-5.55060;-1.74292;,
 19.45164;1.50236;1.83543;,
 19.45164;1.50236;-1.74292;,
 18.65044;-4.96469;1.83543;,
 18.65044;-4.96469;-1.74292;,
 19.73199;-4.15218;-1.74292;,
 19.73199;-4.15218;1.83543;,
 19.06868;-3.79832;-6.22168;,
 18.21990;-4.64716;-6.22168;,
 17.37112;-3.79832;-6.22168;,
 18.21990;-2.94952;-6.22168;,
 19.06868;-3.79832;6.31421;,
 18.21990;-2.94952;6.31421;,
 17.37112;-3.79832;6.31421;,
 18.21990;-4.64716;6.31421;,
 2.42693;7.13658;-6.22168;,
 1.57813;6.28774;-6.22168;,
 0.72931;7.13658;-6.22168;,
 1.57813;7.98538;-6.22168;,
 2.42693;7.13658;6.31421;,
 1.57813;7.98538;6.31421;,
 0.72931;7.13658;6.31421;,
 1.57813;6.28774;6.31421;,
 15.66936;13.01146;-0.81690;,
 15.53527;11.88919;-1.93919;,
 15.62092;13.01146;-3.06147;,
 15.69951;14.13375;-1.93919;,
 15.66936;13.01146;0.90941;,
 15.69951;14.13375;2.03169;,
 15.62092;13.01146;3.15398;,
 15.53527;11.88919;2.03169;,
 15.36511;9.78316;-3.14560;,
 15.24511;8.19602;-3.14560;,
 15.24028;8.19602;-4.73277;,
 15.36162;9.78316;-4.73277;,
 15.36511;9.78316;3.23811;,
 15.36162;9.78316;4.82528;,
 15.24028;8.19602;4.82528;,
 15.24511;8.19602;3.23814;,
 15.24389;8.24759;-3.14560;,
 15.79394;7.29803;-3.14560;,
 15.78918;7.34742;-4.73277;,
 15.24038;8.24759;-4.73277;,
 15.24389;8.24759;3.23811;,
 15.24038;8.24759;4.82528;,
 15.78918;7.34742;4.82528;,
 15.79394;7.29803;3.23814;,
 15.38564;18.29425;1.41302;,
 15.38564;18.29425;-1.32049;,
 13.65742;20.02882;-1.53318;,
 13.65742;20.02882;1.62569;;
 
 56;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 3;10,0,11;,
 3;12,1,0;,
 3;13,4,1;,
 3;14,6,4;,
 3;15,8,6;,
 3;16,17,3;,
 3;18,3,2;,
 3;19,2,5;,
 3;20,5,7;,
 3;21,7,9;,
 4;22,23,24,25;,
 4;26,27,28,29;,
 4;30,31,32,33;,
 4;34,35,36,37;,
 4;38,39,40,41;,
 4;42,43,44,45;,
 4;46,47,48,49;,
 4;46,43,50,51;,
 4;52,53,54,55;,
 4;56,57,58,59;,
 4;60,61,62,63;,
 4;60,53,64,65;,
 4;66,67,54,63;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;76,73,80,81;,
 4;82,83,84,85;,
 4;86,87,88,89;,
 4;90,91,92,93;,
 4;90,83,94,95;,
 4;96,97,84,93;,
 4;98,99,100,101;,
 4;102,103,104,105;,
 4;106,107,108,109;,
 4;110,111,104,109;,
 4;112,113,114,115;,
 4;116,117,118,119;,
 4;120,121,122,123;,
 4;120,117,124,125;,
 4;126,127,128,129;,
 4;130,131,132,133;,
 4;134,135,136,137;,
 4;138,139,140,141;,
 4;142,143,144,145;,
 4;146,147,148,149;,
 4;150,151,152,153;,
 4;154,155,156,157;,
 4;158,159,160,161;,
 4;162,163,164,165;,
 4;166,167,168,169;,
 4;170,171,172,173;;
 
 MeshMaterialList {
  6;
  56;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.960784;0.784314;0.007843;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.141961;0.141961;0.141961;1.000000;;
   0.000000;
   0.100000;0.100000;0.100000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;0.615686;0.000000;1.000000;;
   100.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.466667;1.000000;1.000000;;
   100.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.466667;1.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  35;
  0.000000;0.000000;-1.000000;,
  0.774952;-0.632020;-0.000000;,
  -0.269181;0.963090;0.000002;,
  -1.000000;0.000000;0.000000;,
  0.425002;-0.905192;-0.000000;,
  0.000000;0.000000;1.000000;,
  -0.970296;-0.241922;0.000000;,
  0.608764;-0.793352;-0.000000;,
  -0.938972;-0.343994;0.000000;,
  0.058694;0.131994;0.989511;,
  0.058694;0.131994;-0.989511;,
  0.709154;0.705053;0.000000;,
  0.938516;0.345236;0.000000;,
  0.971485;-0.237100;-0.000000;,
  0.989221;0.146433;0.000000;,
  0.024197;0.024375;-0.999410;,
  0.024197;0.024375;0.999410;,
  0.998715;0.050686;0.000000;,
  0.600640;-0.799520;-0.000000;,
  0.997106;-0.072914;-0.021517;,
  0.997106;-0.072914;0.021517;,
  0.997119;-0.075809;-0.002615;,
  0.997119;-0.075809;0.002615;,
  0.859609;0.510922;0.005555;,
  0.859609;0.510922;-0.005556;,
  0.708402;0.705809;0.000000;,
  -0.008710;-0.999962;0.000000;,
  -0.241921;0.970296;0.000000;,
  0.863174;0.504907;0.000000;,
  -0.863176;-0.504903;0.000000;,
  -0.048438;0.998826;0.000000;,
  -0.998045;0.062499;0.000000;,
  0.996997;-0.077440;-0.000000;,
  0.861133;0.508380;0.000000;,
  -0.361078;0.932536;0.000000;;
  56;
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;26,4,4,26;,
  4;4,1,1,4;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;27,27,27,27;,
  4;0,0,0,0;,
  4;7,7,7,7;,
  4;5,5,5,5;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;8,8,8,8;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;30,30,30,30;,
  4;10,10,10,10;,
  4;11,11,12,12;,
  4;9,9,9,9;,
  4;31,31,31,31;,
  4;32,32,12,12;,
  4;13,13,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;14,14,33,33;,
  4;17,17,17,17;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;34,34,34,34;,
  4;18,18,18,18;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;24,24,24,24;,
  4;25,25,25,25;;
 }
 MeshTextureCoords {
  174;
  0.200000;0.000000;,
  0.400000;0.000000;,
  0.400000;1.000000;,
  0.200000;1.000000;,
  0.600000;0.000000;,
  0.600000;1.000000;,
  0.800000;0.000000;,
  0.800000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.100000;0.000000;,
  0.000000;0.000000;,
  0.300000;0.000000;,
  0.500000;0.000000;,
  0.700000;0.000000;,
  0.900000;0.000000;,
  0.100000;1.000000;,
  0.000000;1.000000;,
  0.300000;1.000000;,
  0.500000;1.000000;,
  0.700000;1.000000;,
  0.900000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;;
 }
}
