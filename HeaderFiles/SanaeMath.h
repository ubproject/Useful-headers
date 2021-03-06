#pragma once
#ifndef INCLUDE_GUARD_SANAEMATH_H
#define INCLUDE_GUARD_SANAEMATH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <vector>

//二乗します
template<class T>inline T squared(T data) { return(data * data); };
//絶対値にします
template<class T>inline T absv(T data) { return data < 0 ? -(data) : data; };
namespace sanae {
	/*-----------------------------------------------
	* Project:SanaeProject-UsefulHeadersProject
	* Dev:SanaeProject
	* Function:
	This header have many math functions.
	*Copyright 2021 SanaeProject.ALL Rights Reserved.
	-----------------------------------------------*/
	namespace math {
		/*桁数を返す*/
		unsigned int digit(int t) {
			unsigned int digit = 0;
			for (int i = 1;; i = i * 10) {
				if ((t / i) != 0 || (t / i) > 0) { digit += 1; }
				else break;
			}
			return digit-1;
		}
		/* ニュートン法を利用して平方根の計算を行う */
		double root(long double t) {
			/*引用:https://schlaf.ltd/programming/c/c-square-root/ */
			if (t == 0) {
				return 0;
			}
			else if (t == 1) { return 1; }
			double y = 0, x = 1;
			while (1) {
				x = x - (x * x - t) / (2 * x);
				y = x * x - t;
				if ((y <= 0.00000001) && (y >= -0.00000001)) {
					break;
				}
			}
			return x;
		}
		/*小数点は何桁あるかを返します。*/
		int little_digit(double t) {
			if (t == (int)t)return 0;
			for (long i = 10, i2 = 1;; i = i * 10, i2++) {
				if ((t * i) > 0 && (t * i) - (int)(t * i) == 0) {
					return i2;
				}
			}
		}
		/*3平方の定理で求める*/
		template<class T>
		double triangle(T a, T b, bool calculation_root = true) {
			double answer = 0;
			if (calculation_root) {
				answer = sanae::math::root(((long double)a * (long double)a) + ((long double)b * (long double)b));
			}
			else {
				answer = ((long double)a * (long double)a) + ((long double)b * (long double)b);
			}
			return answer;
		}
		//平均値を返す
		template<typename T>
		double array_average(int count, T* t) {
			T data = 0;
			for (int i = 0; i < count; i++) {
				data += *(t + i);
			}
			return data / count;
		}
		//標準偏差を返す
		template<typename T>
		double array_deviation(int count, T* datas, bool to_distributed = false) {
			T average_value = array_average(count, datas);
			for (int i = 0; i < count; i++) {
				*(datas + i) = *(datas + i) - average_value;
				double s = *(datas + i);
				*(datas + i) = s * s;
			}
			double v = 0;
			if (!to_distributed) {
				v = root(array_average(count, datas));
			}
			else {
				v = array_average(count, datas);
			}
			return v;
		}
		/*偶数か判定します。*/
		bool is_even(int i) {
			if (i % 2 == 0)return true;
			return false;
		}
		/*素数判定を返します。*/
		bool is_primenumber(int i) {
			if (i <= 1) {
				return false;
			}
			else if (i == 2) {
				return true;
			}
			if (i % 2 == 0) {
				return false;
			}
			int i2 = (int)sanae::math::root(i) + 1;
			for (int i1 = 3; i1 < i2; i1 += 2) {
				if (i % i1 == 0) {
					return false;
				}
			}
			return true;
		}
#ifdef INCLUDE_GUARD_SANAEUTIL_H
		/*N次元の2個のデータのユークリッド距離を返します。*/
		template<typename T>
		double euclidean(T* data1, T* data2, int count) {
			std::vector<T> datas;
			for (unsigned int i = 0; i < count; i++) {
			datas.push_back(data1[i] - data2[i]);
			}
			double d = 0;
			for (unsigned int i = 0; i < datas.len(); i++) {
				d += datas[i] * datas[i];
			}
			d = sanae::math::root(d);
			return d;
		}
		/*平面ベクトルのクラスです。*/
		template<typename T>
		class vector_math {
		private:
			sanae::util::pair<T, T> data;
		public:
			/*operator*/
			T operator [](int number) {
				return number==0?data.first():data.second();
			}
			//+
			void operator +=(sanae::math::vector_math<T> _data) {
				data={ data.first() + _data[0],data.second() + _data[1] };
			}
			sanae::util::pair<T, T> operator +(sanae::math::vector_math<T> _data) {
				return {data.first()+_data[0],data.second()+_data[1]};
			}
			//-
			void operator -=(sanae::math::vector_math<T> _data) {
				data = { data.first() - _data[0],data.second() - _data[1] };
			}
			sanae::util::pair<T, T> operator -(sanae::math::vector_math<T> _data) {
				return {data.first()-_data[0],data.second()-_data[1]};
			}
			//*
			void operator *=(sanae::math::vector_math<T> _data) {
				data = { data.first() * _data[0],data.second() * _data[1] };
			}
			sanae::util::pair<T, T> operator *(sanae::math::vector_math<T> _data) {
				return {data.first() * _data[0],data.second() * _data[1]};
			}
			/*最小値にします。*/
			void to_minimum() {
				for (int i = 1; i<=data.first()&&i<= data.second();i++) {
					if (data.first() % i == 0) {
						if (data.second() % i == 0) {
							data.set(data.first() / i, data.second() / i);
							i = 1;
						}
					}
				}
			}
			/*X軸の値を返します。*/
			T getX() { return data.first(); }
			/*X軸の値を返します。*/
			T getY() { return data.second(); }
			/*ベクトルの成分を代入してください。*/
			vector_math(T _d1, T _d2){data.set(_d1,_d2);}
			/*ベクトルの成分を代入してください。*/
			vector_math(sanae::util::pair<T,T> _data):data(_data){}
			/*代入されたベクトルの2データの成分を自動で計算して代入します。
			{{ベクトルの始点}{ベクトルの終点}}*/
			vector_math(sanae::util::pair<T, T> _data1,sanae::util::pair<T,T> _data2){
				this->data={_data2.first()-_data1.first(),_data2.second()-_data1.second()};
			}
			double volume(bool calculation_root=true) {
				return calculation_root ? sanae::math::root((data.first()*data.first())+(data.second()*data.second())):(data.first()*data.first())+(data.second()*data.second());
			}
		};
		/*相関係数を返します。*/
		template<typename T>
		double correlation(T* d1, T* d2, int count) {
			double data1 = sanae::math::array_average(count, d1);
			double data2 = sanae::math::array_average(count, d2);
			double* a1 = (double*)malloc(sizeof(double) * count);
			double* a2 = (double*)malloc(sizeof(double) * count);
			if (a1 == NULL || a2 == NULL) { printf("\nメモリの確保に失敗しました。\n"); exit(0); }
			//偏差積を出す
			std::vector<double> a3;
			//偏差を出すd1,d2
			for (int i = 0; i < count; i++) { a1[i] = (d1[i] - data1); }
			for (int i = 0; i < count; i++){a2[i] = (d2[i] - data2);}
			//偏差の積を出す
			for (int i = 0; i < count; i++) { a3.push_back(a1[i] * a2[i]); }
			double _d = 0;
			for (int i = 0; i < a3.size(); i++) { _d += a3[i]; }
			free(a1); free(a2);
			_d = _d / a3.size();
			data1 = sanae::math::array_deviation(count, d1);
			data2 = sanae::math::array_deviation(count, d2);
			return _d / (data1 * data2);
		}
		/*渡された配列の最小値を返します*/
		template<typename T>
		T min(int count, T* data) {
			T min=data[0];
			for (int i = 1; i < count;i++) {
				if (min> data[i]) {
					min = data[i];
				}
			}
			return min;
		}
		template<typename T>
		T min(std::vector<T> data) {
			T min = data[0];
			for (int i = 1; i < data.size();i++) {
				if (min>data[i]) {
					min = data[i];
				}
			}
			return min;

		}
		/*N次元の2個のデータのユークリッド距離を返します。*/
		template<typename T>
		double euclidean(std::vector<T> data1,std::vector<T> data2) {
			std::vector<T> datas = { 0,0 };
			if (data1.len() == data2.len()) {
				for (int i = 0; i < data1.len(); i++) {datas.push_back(data1[i] - data2[i]);}
				double d = 0;
				for (int i = 0; i < datas.len(); i++) {d += datas[i] * datas[i];}
				d = sanae::math::root(d);
				return d;
			}
			else {
				return 0.0;
			}
		}
		/*掛け算を返します。
		第二引数の値を入れることで指定した値から掛け算を検索できます。
		*/
		sanae::util::pair<int, int> division_number_parts(int root, int startpoint = 2) {
			if (startpoint <= 1) {
				startpoint = 2;
			}
			if (is_primenumber(root)) {
				sanae::util::pair<int, int> an = { root,0 };
				return an;
			}
			sanae::util::pair<int, int> answer = { 0,0 };
			if (root == 4) { answer = { 2,2 }; return answer; }
			for (int i = startpoint; i <= root; i++) {
				if (is_primenumber(i)) {
					if (little_digit(root / i) == 0) {
						if ((root / i) * i == root) {
							answer = { i,root / i };
							return answer;
						}
					}
				}
			}
			return answer;
		}
		/*入力された値の素数の組み合わせを返します*/
		std::vector<int> division_number(int number) {
			std::vector<int> answer;
			if (is_primenumber(number)) {
				answer.push_back(number);
				return answer;
			}
			sanae::util::pair<int, int> test = { 0,number };
			for (;;) {
				test = division_number_parts(test.second());
				answer.push_back(test.first());
				if (is_primenumber(test.second())) {
					answer.push_back(test.second());
					break;
				}
				if (test.second() == 0) {
					break;
				}
			}
			return answer;
		}
#endif
	}
}
#endif