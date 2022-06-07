#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <initializer_list>
#include <limits>
#include <vector>
#include <tuple>
#include <memory>
#include <string>
#include <stdio.h>
#include <cstdio>

using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::ofstream;
using std::vector;
using std::tuple;
using std::tie;
using std::make_tuple;
using std::shared_ptr;
using std::vector;
using std::rank;
#include "io.h"
#include "matrix.h"

#include "MyObject.h"

struct crd {
  int x[1000];
  int y[1000];
  int size = 0;
};



void binar (Image &in, Matrix<int> &bin) {
  uint n_r = in.n_rows, n_c = in.n_cols;
  uint red, green, blue, h = 175;
  for (uint i = 0; i < n_r; i++) {
    for (uint j = 0; j < n_c; j++) {
      tie (red, green, blue) = in (i, j);
      if (red > h || green > h || blue > h) {
        bin (i, j) = 1;
      }
      else {
        bin (i, j) = 0;
      }
    }
  }
}


void bl_wh (Image &in, Matrix<int> &bin) {
  uint r, g, b;
  uint n_r = bin.n_rows, n_c = bin.n_cols;
  for (uint i = 0; i < n_r; i++)
    for (uint j = 0; j < n_c; j++) {
      if(bin(i, j) == 0) {
        r = 0; g = 0; b = 0;
        in (i, j) = make_tuple (r, g, b);
      }
      else {
          r = 255, g = 255, b = 255;
          in (i, j) = make_tuple (r, g , b);
      }
    }
}

crd crds[1000];
void scan(Matrix<int> &bin) {
  uint n_r = bin.n_rows , n_c = bin.n_cols;
  int g_numb = 1;
  uint i = 0, j = 0;
  int kn = 0;
  int km = 0;
  for (i = 1; i < n_r; i ++) {
    for (j = 1; j < n_c; j++) {
      int b = 0;
      int c = 0;
      int a = 0;

      kn = j - 1;
      if (kn <= 0) {
        kn = 1;
        b = 0;
      }
      else
        b = bin(i, kn);

      km = i - 1;
      if (km <= 0) {
        km = 1;
        c = 0;
      }
      else
        c = bin(km, j);

      a = bin(i, j);

      if (a == 0) {}

      else if (b == 0 && c == 0) {
        g_numb++;
        bin(i, j) = g_numb;
        crds[g_numb].x[crds[g_numb].size] = i;
        crds[g_numb].y[crds[g_numb].size] = j;
        crds[g_numb].size++;
      }
      else if (b!= 0 && c == 0) {
        bin(i, j) = b;
        crds[b].x[crds[b].size] = i;
        crds[b].y[crds[b].size] = j;
        crds[b].size++;
      }
      else if (b == 0 && c!= 0) {
         bin(i, j) = c;
         crds[c].x[crds[c].size] = i;
         crds[c].y[crds[c].size] = j;
         crds[c].size++;
      }
      else if (b!= 0 && c!= 0) {
          if (b == c) {
            bin(i, j) = b;
            crds[b].x[crds[b].size] = i;
            crds[b].y[crds[b].size] = j;
            crds[c].size++;
          }
          else {
              if (b > c) {
                  bin(i, j) = c;
                  crds[c].x[crds[c].size] = i;
                  crds[c].y[crds[c].size] = j;
                  crds[c].size++;
                  for (int k = 0; k < crds[b].size; k++) {
                    bin (crds[b].x[k], crds[b].y[k]) = c;
                    crds[c].x[crds[c].size] = crds[b].x[k];
                    crds[c].y[crds[c].size] = crds[b].y[k];
                    crds[c].size++;
                  }
                  crds[b].size = 0;
                }
              else {
                  bin(i, j) = b;
                  crds[b].x[crds[b].size] = i;
                  crds[b].y[crds[b].size] = j;
                  crds[b].size++;
                  for (int l = 0; l < crds[c].size; l++) {
                    bin (crds[c].x[l], crds[c].y[l]) = b;
                    crds[b].x[crds[b].size] = crds[c].x[l];
                    crds[b].y[crds[b].size] = crds[c].y[l];
                    crds[b].size++;
                  }
                  crds[c].size = 0;
              }
           }
        }
     }
  }
  cout << "\n";
}



void check (Image &in, Matrix<int> &bin) {
  uint n_r = in.n_rows, n_c = in.n_cols;
  for (uint i = 0; i < n_r; i++)
    for (uint j = 0; j < n_c; j++) {

      if (bin(i , j) == 2) {
          in (i, j) = make_tuple (255, 255, 0);
        }
        if (bin(i , j) == 65) {
          in (i, j) = make_tuple (255, 0, 0);
        }
        if (bin(i , j) == 130) {
          in (i, j) = make_tuple (0, 255, 0);
        }
        if (bin(i , j) == 201) {
          in (i, j) = make_tuple (0, 0, 255);
        }
        if (bin(i , j) == 265) {
          in (i, j) = make_tuple (0, 255, 255);
        }
        if (bin(i , j) == 280) {
          in (i, j) = make_tuple (255, 0, 255);
        }
        if (bin(i , j) == 316) {
          in (i, j) = make_tuple (192, 192, 192);
        }
        if (bin(i , j) == 362) {
          in (i, j) = make_tuple (128, 128, 128);
        }
    }
}

bool check(vector <int> ch, int a) {
  bool put = true;
  for (uint i = 0; i < ch.size(); i++) {
    if (ch[i] == a) put = false;
  }
  return put;
}

vector <int> my_objs;
void Objects(Matrix <int> bin) {
  uint c_r = bin.n_rows;
  uint c_c = bin.n_cols;

  for (uint i = 1; i < c_r; i++)
    for (uint j = 1; j < c_c; j++)
        if ((bin(i, j)!= 0) && (check(my_objs, bin(i, j)) == true)) {
          my_objs.push_back(bin(i, j));
      }
}

vector <int> ss;
int mass(Matrix<int> bin) {
  int su = 0;
  uint c_r = bin.n_rows;
  uint c_c = bin.n_cols;
  for (uint k = 0; k < my_objs.size(); k++) {
    for (uint i = 1; i < c_r; i++) {
      for (uint j = 1; j < c_c; j++)
          if (bin(i, j) == my_objs[k])
            su++;
    }
    ss.push_back(su);
    su = 0;
  }
  int min = ss[0];
  for (uint i = 0; i < ss.size(); i++)
    if(min > ss[i]) min = ss[i];
  return min;
}

int mass1(Matrix <int> bin, int n) {
  int su = 0;
  uint c_r = bin.n_rows;
  uint c_c = bin.n_cols;
    for (uint i = 1; i < c_r; i++)
      for (uint j = 1; j < c_c; j++)
          if (bin(i, j) == n)
            ++su;
  return su;
}

int foo(Matrix <int> bin, int n, int k) {
  int su = 0;
  int pp = 0;
  uint c_r = bin.n_rows;
  uint c_c = bin.n_cols;
    for (uint i = 1; i < c_r; i++)
      for (uint j = 1; j < c_c; j++)
          if (bin(i, j) == k){
            su++;
          }
  if (n == su){ pp = k; return pp;}
  else return 0;
}

vector <int> centersx;
vector <int> centersy;
void Centre(Matrix<int> bin, int obj, uint s) {
  uint c_r = bin.n_rows;
  uint c_c = bin.n_cols;
  uint x = 0, y = 0;
  //uint sumx = 0, sumy = 0;
  for (uint i = 1; i < c_r; i++)
    for (uint j = 1; j < c_c; j++) {
      if (bin(i, j) == obj) {
        y += j;
        x += i;
      }
  }
  x = x/s;
  centersx.push_back(x);
  y = y/s;
  centersy.push_back(y);
  cout <<  "x " << x << "\n" << "y " << y << endl;
}

int distance(Matrix<int> bin) {
  int x;
  int y1;
  int y2;
  int buf;
  vector <int>res;
  uint c_r = bin.n_rows;
  uint n_c = bin.n_cols;
  bool flag = false;
  for (uint i = 1; i < c_r; i++) {
      for (uint j = 1; j < n_c; j++) {
          if ((bin(i, j) == 130) && (bin(i, j+1) == 0)) {
          //  cout << "in";
              x = i;
              y1 = j;
              flag = true;
          }
          if (flag == true)
            if (bin(x, j) == 265) {
              y2 = j;
              buf = y2 - y1;
              res.push_back(buf);
            }
      }
    flag = false;
  }
  int min = res[0];
  int max = res[0];
  for (uint i = 0; i < ss.size(); i++) {
    if(max < res[i]) max = res[i];
    if(min > res[i]) min = res[i];
  }
//  cout << "max " << max << "\n" << "min " << min << endl;
  return max;
}

int diametr(Matrix<int> bin, int n) {
  uint n_r = bin.n_rows;
  uint n_c = bin.n_cols;
  vector<int> diams;
  int x;
  int y1, y2;
  int buf;
  int max;
  bool flag = false;
  for (uint i = 1; i < n_r; i++) {
    for (uint j = 1; j < n_c; j++){
      if (bin(i, j) == n && bin(i, j-1)== 0) {
        x = i;
        y1 = j;
        flag = true;
      }
      if (flag == true)
        if (bin(x,j) == 0) {
          y2 = j;
          buf = y2 - y1;
          diams.push_back(buf);
          flag = false;
        }
    }
    flag = false;
  }
  max = diams[0];
  for (uint i = 0; i < diams.size(); i++)
   if(max < diams[i]) max = diams[i];
  //cout << "maxD " << max << endl;
  return max;
}

void recollor(Matrix<int> bin, int n) {
  uint n_r = bin.n_rows;
  uint n_c = bin.n_cols;
  for (uint i = 1; i < n_r; i++)
    for (uint j = 1; j < n_c; j++)
      if(bin(j, j) == 1)
        bin(i, j) = n;
}


vector <int> x2;
vector <int> y2;
void funk(Matrix<int> bin) {
  for (uint i = 1; i < bin.n_rows; i++)
    for (uint j = 1; j < bin.n_cols; j++)
      if (bin(i, j)!=0) {
        x2.push_back(i);
        y2.push_back(j);
      }
cout << "sizex " <<x2.size() << "sizey " << y2.size() << endl;
}


void inp (Matrix<int> bin) {
  cout << "x2: " << x2.size() << "y2: " << y2.size() << endl;
  for (uint i0 = 0, j0 = 0; i0 < x2.size(); i0++, j0++) {
    uint i = x2[i0] + centersx[0]- centersx[1];
    uint j = y2[j0] + centersy[0]- centersy[1];
   bin(i, j) = 65;
  }
}



int obj1;

tuple<int, vector<shared_ptr<IObject>>, Image>
repair_mechanism(Image& in)
{
    // Base: return array of found objects and index of the correct gear
    Matrix<int> binImg(in.n_rows, in.n_cols);
    auto object_array = vector<shared_ptr<IObject>>();
    int result_idx = 0;
  //  int dis;
    int minmass;
    vector<Image> var;
    vector<char*> name;
    for (int i = 0; i < 3; i++) {
      char obj[30] = {0};
      Image im;
      snprintf(obj, 30, "./../data/pic/0002_%d.bmp", i+1);
      name.push_back(obj);
      var.push_back(im);
      var[i] = load_image(name[i]);
      cout << name[i] << " ";
    }
  //  cout << "s =" << binImg.n_rows * binImg.n_cols << endl;
    binar (in, binImg);
    bl_wh (in, binImg);
    scan (binImg);
    check (in, binImg);
    Objects(binImg);
    minmass = mass(binImg);
    for (uint k = 0; k < my_objs.size(); k++) {
      if ((foo(binImg, minmass, my_objs[k]))!= 0)
      obj1 = foo(binImg, minmass, my_objs[k]);
    }
    cout << "OBJ1" << obj1 << endl;
    Centre(binImg, obj1, minmass);
    //dis = distance(binImg);
    /////////////////////////////////////////////////////////////////////
    for (int i = 0; i < 3; i++) {
      int ldia;
      Matrix<int> lblImg(var[i].n_rows, var[i].n_cols);
      binar(var[i], lblImg);
      ldia = diametr(lblImg, 1);
      int checking = ((300 - ldia)/2);
      if (checking >= 40 && checking <= 70) {
        //recollor (lblImg, obj1);
        cout << "MASS " << mass1(lblImg, 1) << endl;
        Centre(lblImg, 1 , mass1(lblImg, 1));
        cout << "cx[0] = " << centersx[0] << "cx[1]" << centersx[1] << endl;
        cout << "cy[0] = " << centersy[0] << "cy[1]" << centersy[1] << endl;
        funk(lblImg);
        inp(binImg);
        check(in ,binImg);
        break;
      }
    }
    return make_tuple(result_idx, object_array, in.deep_copy());
}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        cout << "Usage: " << endl << argv[0]
             << " <in_image.bmp> <out_image.bmp> <out_result.txt>" << endl;
        return 0;
    }

    try {
        Image src_image = load_image(argv[1]);
        ofstream fout(argv[3]);

        vector<shared_ptr<IObject>> object_array;
        Image dst_image;
        int result_idx;
        tie(result_idx, object_array, dst_image) = repair_mechanism(src_image);
        save_image(dst_image, argv[2]);

        fout << result_idx << endl;
        fout << object_array.size() << endl;
        for (const auto &obj : object_array)
            obj->Write(fout);

    } catch (const string &s) {
        cerr << "Error: " << s << endl;
        return 1;
    }
}
