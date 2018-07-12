/*******************************************************************************
  Title          : haversine.h
  Author         : Stewart Weiss
  Created on     : October 30, 2017
  Description    : Computes distance between two points on earth 
  Purpose        : 
  Usage          : haversine latitude1 longitude1 latitude2 longitude2 in degrees
  Build with     : gcc -o haversine haversine.v -lm
  Modifications  : 
 
*******************************************************************************/
#ifndef __HAVERSINE_H__
#define __HAVERSINE_H__

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
 
#define RA 6372.8
#define TO_RAD (3.1415926536 / 180)

double dist(double th1, double ph1, double th2, double ph2);

double haversine(double lat1, double lon1, double lat2, double lon2);

#endif
