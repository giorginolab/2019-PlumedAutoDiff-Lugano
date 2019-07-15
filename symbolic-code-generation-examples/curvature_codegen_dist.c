/******************************************************************************
 *                       Code generated with sympy 1.0                        *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                  This file is part of 'plumed_curvature'                   *
 ******************************************************************************/
#include "curvature_codegen_dist.h"
#include <math.h>

double curvature_radius_dist(double r_12x, double r_12y, double r_12z, double r_13x, double r_13y, double r_13z, double r_23x, double r_23y, double r_23z) {

   double curvature_radius_dist_result;
   curvature_radius_dist_result = (1.0L/2.0L)*sqrt((pow(r_13x, 2) + pow(r_13y, 2) + pow(r_13z, 2))/(1 - pow(r_12x*r_23x + r_12y*r_23y + r_12z*r_23z, 2)/((pow(r_12x, 2) + pow(r_12y, 2) + pow(r_12z, 2))*(pow(r_23x, 2) + pow(r_23y, 2) + pow(r_23z, 2)))));
   return curvature_radius_dist_result;

}

void curvature_radius_grad_dist(double r_12x, double r_12y, double r_12z, double r_13x, double r_13y, double r_13z, double r_23x, double r_23y, double r_23z, double *g) {

   g[0] = (1.0L/4.0L)*sqrt((pow(r_13x, 2) + pow(r_13y, 2) + pow(r_13z, 2))/(1 - pow(r_12x*r_23x + r_12y*r_23y + r_12z*r_23z, 2)/((pow(r_12x, 2) + pow(r_12y, 2) + pow(r_12z, 2))*(pow(r_23x, 2) + pow(r_23y, 2) + pow(r_23z, 2)))))*(-2*r_12x*pow(r_12x*r_23x + r_12y*r_23y + r_12z*r_23z, 2)/(pow(pow(r_12x, 2) + pow(r_12y, 2) + pow(r_12z, 2), 2)*(pow(r_23x, 2) + pow(r_23y, 2) + pow(r_23z, 2))) + 2*r_23x*(r_12x*r_23x + r_12y*r_23y + r_12z*r_23z)/((pow(r_12x, 2) + pow(r_12y, 2) + pow(r_12z, 2))*(pow(r_23x, 2) + pow(r_23y, 2) + pow(r_23z, 2))))/(1 - pow(r_12x*r_23x + r_12y*r_23y + r_12z*r_23z, 2)/((pow(r_12x, 2) + pow(r_12y, 2) + pow(r_12z, 2))*(pow(r_23x, 2) + pow(r_23y, 2) + pow(r_23z, 2))));
   g[1] = (1.0L/4.0L)*sqrt((pow(r_13x, 2) + pow(r_13y, 2) + pow(r_13z, 2))/(1 - pow(r_12x*r_23x + r_12y*r_23y + r_12z*r_23z, 2)/((pow(r_12x, 2) + pow(r_12y, 2) + pow(r_12z, 2))*(pow(r_23x, 2) + pow(r_23y, 2) + pow(r_23z, 2)))))*(-2*r_12y*pow(r_12x*r_23x + r_12y*r_23y + r_12z*r_23z, 2)/(pow(pow(r_12x, 2) + pow(r_12y, 2) + pow(r_12z, 2), 2)*(pow(r_23x, 2) + pow(r_23y, 2) + pow(r_23z, 2))) + 2*r_23y*(r_12x*r_23x + r_12y*r_23y + r_12z*r_23z)/((pow(r_12x, 2) + pow(r_12y, 2) + pow(r_12z, 2))*(pow(r_23x, 2) + pow(r_23y, 2) + pow(r_23z, 2))))/(1 - pow(r_12x*r_23x + r_12y*r_23y + r_12z*r_23z, 2)/((pow(r_12x, 2) + pow(r_12y, 2) + pow(r_12z, 2))*(pow(r_23x, 2) + pow(r_23y, 2) + pow(r_23z, 2))));
   g[2] = (1.0L/4.0L)*sqrt((pow(r_13x, 2) + pow(r_13y, 2) + pow(r_13z, 2))/(1 - pow(r_12x*r_23x + r_12y*r_23y + r_12z*r_23z, 2)/((pow(r_12x, 2) + pow(r_12y, 2) + pow(r_12z, 2))*(pow(r_23x, 2) + pow(r_23y, 2) + pow(r_23z, 2)))))*(-2*r_12z*pow(r_12x*r_23x + r_12y*r_23y + r_12z*r_23z, 2)/(pow(pow(r_12x, 2) + pow(r_12y, 2) + pow(r_12z, 2), 2)*(pow(r_23x, 2) + pow(r_23y, 2) + pow(r_23z, 2))) + 2*r_23z*(r_12x*r_23x + r_12y*r_23y + r_12z*r_23z)/((pow(r_12x, 2) + pow(r_12y, 2) + pow(r_12z, 2))*(pow(r_23x, 2) + pow(r_23y, 2) + pow(r_23z, 2))))/(1 - pow(r_12x*r_23x + r_12y*r_23y + r_12z*r_23z, 2)/((pow(r_12x, 2) + pow(r_12y, 2) + pow(r_12z, 2))*(pow(r_23x, 2) + pow(r_23y, 2) + pow(r_23z, 2))));
   g[3] = (1.0L/2.0L)*r_13x*sqrt((pow(r_13x, 2) + pow(r_13y, 2) + pow(r_13z, 2))/(1 - pow(r_12x*r_23x + r_12y*r_23y + r_12z*r_23z, 2)/((pow(r_12x, 2) + pow(r_12y, 2) + pow(r_12z, 2))*(pow(r_23x, 2) + pow(r_23y, 2) + pow(r_23z, 2)))))/(pow(r_13x, 2) + pow(r_13y, 2) + pow(r_13z, 2));
   g[4] = (1.0L/2.0L)*r_13y*sqrt((pow(r_13x, 2) + pow(r_13y, 2) + pow(r_13z, 2))/(1 - pow(r_12x*r_23x + r_12y*r_23y + r_12z*r_23z, 2)/((pow(r_12x, 2) + pow(r_12y, 2) + pow(r_12z, 2))*(pow(r_23x, 2) + pow(r_23y, 2) + pow(r_23z, 2)))))/(pow(r_13x, 2) + pow(r_13y, 2) + pow(r_13z, 2));
   g[5] = (1.0L/2.0L)*r_13z*sqrt((pow(r_13x, 2) + pow(r_13y, 2) + pow(r_13z, 2))/(1 - pow(r_12x*r_23x + r_12y*r_23y + r_12z*r_23z, 2)/((pow(r_12x, 2) + pow(r_12y, 2) + pow(r_12z, 2))*(pow(r_23x, 2) + pow(r_23y, 2) + pow(r_23z, 2)))))/(pow(r_13x, 2) + pow(r_13y, 2) + pow(r_13z, 2));
   g[6] = (1.0L/4.0L)*sqrt((pow(r_13x, 2) + pow(r_13y, 2) + pow(r_13z, 2))/(1 - pow(r_12x*r_23x + r_12y*r_23y + r_12z*r_23z, 2)/((pow(r_12x, 2) + pow(r_12y, 2) + pow(r_12z, 2))*(pow(r_23x, 2) + pow(r_23y, 2) + pow(r_23z, 2)))))*(2*r_12x*(r_12x*r_23x + r_12y*r_23y + r_12z*r_23z)/((pow(r_12x, 2) + pow(r_12y, 2) + pow(r_12z, 2))*(pow(r_23x, 2) + pow(r_23y, 2) + pow(r_23z, 2))) - 2*r_23x*pow(r_12x*r_23x + r_12y*r_23y + r_12z*r_23z, 2)/((pow(r_12x, 2) + pow(r_12y, 2) + pow(r_12z, 2))*pow(pow(r_23x, 2) + pow(r_23y, 2) + pow(r_23z, 2), 2)))/(1 - pow(r_12x*r_23x + r_12y*r_23y + r_12z*r_23z, 2)/((pow(r_12x, 2) + pow(r_12y, 2) + pow(r_12z, 2))*(pow(r_23x, 2) + pow(r_23y, 2) + pow(r_23z, 2))));
   g[7] = (1.0L/4.0L)*sqrt((pow(r_13x, 2) + pow(r_13y, 2) + pow(r_13z, 2))/(1 - pow(r_12x*r_23x + r_12y*r_23y + r_12z*r_23z, 2)/((pow(r_12x, 2) + pow(r_12y, 2) + pow(r_12z, 2))*(pow(r_23x, 2) + pow(r_23y, 2) + pow(r_23z, 2)))))*(2*r_12y*(r_12x*r_23x + r_12y*r_23y + r_12z*r_23z)/((pow(r_12x, 2) + pow(r_12y, 2) + pow(r_12z, 2))*(pow(r_23x, 2) + pow(r_23y, 2) + pow(r_23z, 2))) - 2*r_23y*pow(r_12x*r_23x + r_12y*r_23y + r_12z*r_23z, 2)/((pow(r_12x, 2) + pow(r_12y, 2) + pow(r_12z, 2))*pow(pow(r_23x, 2) + pow(r_23y, 2) + pow(r_23z, 2), 2)))/(1 - pow(r_12x*r_23x + r_12y*r_23y + r_12z*r_23z, 2)/((pow(r_12x, 2) + pow(r_12y, 2) + pow(r_12z, 2))*(pow(r_23x, 2) + pow(r_23y, 2) + pow(r_23z, 2))));
   g[8] = (1.0L/4.0L)*sqrt((pow(r_13x, 2) + pow(r_13y, 2) + pow(r_13z, 2))/(1 - pow(r_12x*r_23x + r_12y*r_23y + r_12z*r_23z, 2)/((pow(r_12x, 2) + pow(r_12y, 2) + pow(r_12z, 2))*(pow(r_23x, 2) + pow(r_23y, 2) + pow(r_23z, 2)))))*(2*r_12z*(r_12x*r_23x + r_12y*r_23y + r_12z*r_23z)/((pow(r_12x, 2) + pow(r_12y, 2) + pow(r_12z, 2))*(pow(r_23x, 2) + pow(r_23y, 2) + pow(r_23z, 2))) - 2*r_23z*pow(r_12x*r_23x + r_12y*r_23y + r_12z*r_23z, 2)/((pow(r_12x, 2) + pow(r_12y, 2) + pow(r_12z, 2))*pow(pow(r_23x, 2) + pow(r_23y, 2) + pow(r_23z, 2), 2)))/(1 - pow(r_12x*r_23x + r_12y*r_23y + r_12z*r_23z, 2)/((pow(r_12x, 2) + pow(r_12y, 2) + pow(r_12z, 2))*(pow(r_23x, 2) + pow(r_23y, 2) + pow(r_23z, 2))));

}