#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#define NUM_OF_CITIES 51

using namespace std ;
fstream fin ;

struct coordinate {
	
	int cityID ;
	int x ;
	int y ;
	
};

void Read( coordinate *cityLocation ) {
	
	string temp ;
	for ( int i = 0 ; i < 6 ; ++i )
		getline( fin, temp ) ;
	for ( int i = 0 ; i < NUM_OF_CITIES ; ++i )
		fin >> cityLocation[i].cityID >> cityLocation[i].x >> cityLocation[i].y ;
	
} // Read()

bool LoadFile( string fname, coordinate *cityLocation ) {
	
	fin.open( fname.c_str(), ios::in ) ;	// file open / read 
	if ( !fin )
		return false ;
	else {
		Read( cityLocation ) ;
		// "getline" or "get" here (input)
		fin.close() ;
		return true ;
	} // end else 
} // LoadFile()

double Cal2cityDistance( coordinate a, coordinate b ) {
	
	return sqrt( ( a.x-b.x )*( a.x-b.x )+( a.y-b.y )*( a.y-b.y ) ) ;
	
} // Cal2cityDistance()

double CalDistance( coordinate *cityConnection ) {
	
	double sum = 0 ;
	for ( int i = 0 ; i < NUM_OF_CITIES ; ++i )
		sum += Cal2cityDistance( cityConnection[i], cityConnection[(i+1)%NUM_OF_CITIES] ) ;
	
} // CalDistance()

void SwapCo( int a, int b, coordinate *cityConnection ) {

	coordinate temp ;
	temp = cityConnection[a] ;
	cityConnection[a] = cityConnection[b] ;
	cityConnection[b] = temp ;

}

void Generate( coordinate *cityConnection, double &shortestDistance ) {
	
	double temp ;
	int change = 0, a, b ;
	a = rand()%NUM_OF_CITIES ;
	b = rand()%NUM_OF_CITIES ;
	SwapCo( a, b, cityConnection ) ;
	temp = CalDistance( cityConnection ) ;
	if ( temp < shortestDistance )
		shortestDistance = temp ;
	else
		SwapCo( b, a, cityConnection ) ;
	
} // HillClimbing()

void HillClimbing( coordinate *cityLocation, double shortestDistance ) {
	double temp ;
	int maxGeneration = 50000 ;
	for ( int i = 0 ; i < maxGeneration ; ++i ) {
		temp = shortestDistance ;
		Generate( cityLocation, shortestDistance ) ;
		if ( temp != shortestDistance )
			cout << "Generation_" << i+1 << " :\t" << shortestDistance << endl ;
		// for ( int i = 0 ; i < NUM_OF_CITIES ; ++i )
		// 	cout << cityLocation[i].cityID << "¡B" ;
		// cout << endl ; 
	}
	cout << "\nGenerate times :   " << maxGeneration << endl ;
	cout << "Local min length : " << shortestDistance << endl ; 
}

int main() {
	
	coordinate *cityLocation = new coordinate[NUM_OF_CITIES+1] ; 
	// void RandomConnect()
	coordinate *iterShortest, *temp ;
	int iterationNum, change ;
	double shortestDistance = 999999999 ;
	srand( time(NULL) ) ;
	if ( !LoadFile( "eli51_input.txt", cityLocation ) ) {
		cout << "File input error." << endl ;
		return 0 ;
	}
	HillClimbing( cityLocation, shortestDistance ) ;
	system( "Pause" ) ; 
	/*
	for ( int i = 0 ; i < NUM_OF_CITIES ; ++i )
		cout << i << cityLocation[i].x << cityLocation[i].y << endl ; 
	*/
	// cout << CalDistance( cityLocation ) ;
	
	
	/* trash
	for ( int i = 2 ; i < NUM_OF_CITIES ; ++i ) {
		SwapCo( 1, i, cityConnection ) ;
		temp = CalDistance( cityConnection ) ;
		if ( temp < shortestDistance ) {
			change = i ;
			shortestDistance = temp ;
		}
		SwapCo( i, 1, cityConnection ) ;
	}
	trash*/
} // main()

