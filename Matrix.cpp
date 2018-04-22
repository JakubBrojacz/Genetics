#include "Matrix.h"

float Matrix::sigmoid(float x)
{
	//float y = 1 / (1 + exp(-x));
	//return y;
	if (x > 0)
		return 1;
	return 0;
}

Matrix::Matrix(int r, int c) : rows(r),cols(c)
{
	matrix = new float*[rows];
	for (int i = 0; i<rows; i++)
		matrix[i] = new float[cols];
	randomize();
}

Matrix::Matrix(Matrix & d)
	: rows(d.rows), cols(d.cols)
{
	matrix = new float*[rows];
	for (int i = 0; i<rows; i++)
		matrix[i] = new float[cols];
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			matrix[i][j] = d.matrix[i][j];
}

Matrix * Matrix::dot(Matrix * n)
{
	Matrix* result = new Matrix(rows, n->cols);

	if (cols == n->rows) {
		//for each spot in the new matrix
		for (int i = 0; i<rows; i++) {
			for (int j = 0; j<n->cols; j++) {
				float sum = 0;
				for (int k = 0; k<cols; k++) {
					sum += matrix[i][k] * n->matrix[k][j];
				}
				result->matrix[i][j] = sum;
			}
		}
	}

	return result;
}

void Matrix::randomize()
{
	for (int i = 0; i<rows; i++) {
		for (int j = 0; j<cols; j++) {
			matrix[i][j] = ((float)rand() / (float)RAND_MAX)*2.f - 1.f;
		}
	}
}

Matrix * Matrix::singleColumnMatrixFromArray(float * arr, int l)
{
	Matrix* n = new Matrix(l, 1);
	for (int i = 0; i< l; i++) {
		n->matrix[i][0] = arr[i];
	}
	return n;
}

void Matrix::fromArray(float * arr, int l)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix[i][j] = arr[j + i * cols];
		}
	}
}

float * Matrix::toArray()
{
	float* arr = new float[rows*cols];
	for (int i = 0; i< rows; i++) {
		for (int j = 0; j< cols; j++) {
			arr[j + i * cols] = matrix[i][j];
		}
	}
	return arr;
}

Matrix * Matrix::addBias()
{
	Matrix* n = new Matrix(rows + 1, 1);
	for (int i = 0; i<rows; i++) {
		n->matrix[i][0] = matrix[i][0];
	}
	n->matrix[rows][0] = 1;
	return n;
}

Matrix * Matrix::activate()
{
	Matrix* n = new Matrix(rows, cols);
	for (int i = 0; i<rows; i++) {
		for (int j = 0; j<cols; j++) {
			n->matrix[i][j] = sigmoid(matrix[i][j]);
		}
	}
	return n;
}

Matrix * Matrix::removeBottomLayer()
{
	Matrix* n = new Matrix(rows - 1, cols);
	for (int i = 0; i<n->rows; i++) {
		for (int j = 0; j<cols; j++) {
			n->matrix[i][j] = matrix[i][j];
		}
	}
	return n;
}

void Matrix::mutate(float mutationRate)
{

	//mutate EVERY element (why not?)
	for (int i = 0; i<rows; i++) {
		for (int j = 0; j<cols; j++) {
			float r = (float)(rand()) / (float)RAND_MAX;
			if (r<mutationRate) {
				if(	rand()%100 < 75)
					matrix[i][j] += ((float)(rand()) / (float)RAND_MAX - 0.5f)/10.0; //should be gaussRandom, but this works
				else if (rand() % 100 < 75)
					matrix[i][j] += ((float)(rand()) / (float)RAND_MAX - 0.5f) / 5.0;
				else
					matrix[i][j] = ((float)(rand()) / (float)RAND_MAX - 0.5f)*2.0;

				if (matrix[i][j]>1) {
					matrix[i][j] = 1;			//make it not so big
				}
				if (matrix[i][j] <-1) {
					matrix[i][j] = -1;
				}
			}
		}
	}
}

Matrix * Matrix::crossover(Matrix partner)
{
	Matrix* child = new Matrix(rows, cols);

	//random crossover point
	int randC = floor((float)(rand()) / (float)RAND_MAX * (float)cols);
	int randR = floor((float)(rand()) / (float)RAND_MAX * (float)rows);
	for (int i = 0; i<rows; i++) {
		for (int j = 0; j<cols; j++) {

			if ((i< randR) || (i == randR && j <= randC)) { //first from mother
				child->matrix[i][j] = matrix[i][j];
			}
			else { //then from father
				child->matrix[i][j] = partner.matrix[i][j];
			}
		}
	}
	return child;
}

Matrix * Matrix::clone()
{
	Matrix* clone = new Matrix(rows, cols);
	for (int i = 0; i<rows; i++) {
		for (int j = 0; j<cols; j++) {
			clone->matrix[i][j] = matrix[i][j];
		}
	}
	return clone;
}

Matrix::~Matrix()
{
	for (int i = 0; i < rows; i++)
		delete [] matrix[i];
	delete [] matrix;
}

std::ostream & operator<<(std::ostream & out, const Matrix & d)
{
	for (int i = 0; i < d.rows; i++)
	{
		for (int j = 0; j < d.cols; j++)
		{
			out << d.matrix[i][j] << " ";
		}
	}
	out << std::endl;
	return out;
}

std::istream & operator>>(std::istream & in, Matrix & d)
{
	for (int i = 0; i < d.rows; i++)
	{
		for (int j = 0; j < d.cols; j++)
		{
			in >> d.matrix[i][j];
		}
	}
	return in;
}
