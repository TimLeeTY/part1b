#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Tue Jan 31 21:00:09 2017

@author: leetimmy
"""
from math import * 
import matplotlib.pyplot as plt
import matplotlib.animation as anim
from pprint import *

class planet:
    t=0
    def __init__(self, m, x, v):
        self.m=m
        self.x=x
        self.v=v
        self.track=[[],[]]
    def printall(self, det):
        if det==0:
            print('x=[%f,%f], \n v=[%f,%f] \n f==[%f,%f]' ) %(self.x[0],self.x[1],self.v[0],self.v[1],self.f[0],self.f[1])
        else:
            print(' ')
    def sqrdist(self,planet):
        return(sqrt(sum([(self.x[i]-planet.x[i])**2 for i in range(2)]))**3)
    def incrx(self, xin):
        self.x=[a+b for a,b in zip(self.x,xin)]
    def incrv(self, vin):
        for i in range(2):
            self.v[i]+=vin[i]

def force(objlist, G):
    l=len(objlist)
    ftemp=[[[-(objlist[i].x[k]-objlist[i-j-1].x[k])*G*objlist[i-j-1].m*objlist[i].m/objlist[i].sqrdist(objlist[i-j-1]) for k in range(2)] for j in range (l-1)] for i in range(l)]
    for i in range(l):
        objlist[i].f=[sum([ftemp[i][j][k] for j in range (l-1)])   for k in range(2)]


def leapfrog(G, dt, steps, objlist):
    for j in range(steps):  
        for obj in objlist:
            obj.incrx([0.5*dt*i for i in obj.v])
            obj.t+=0.5*dt
        force(objlist,G)
        for obj in objlist:
            obj.incrv([dt*f/obj.m for f in obj.f])
            obj.incrx([0.5*dt*i for i in obj.v])
        for obj in objlist:
            for i in range(2):
                obj.track[i].append(obj.x[i])
            obj.t+=0.5*dt
            
objlist=[planet(1, [0,1], [0.4,0.4]), planet(1, [-1,-1/3], [0,-0.4]), planet(1, [1,1/3], [-0.4,0])]
leapfrog(0.5,0.0002,200000, objlist)
for obj in objlist:
    plt.plot(obj.track[0],obj.track[1])
fig = plt.figure()
ax = plt.axes(xlim=(0, 2), ylim=(-2, 2))
line, = ax.plot([], [], 'o-', lw=2)
def init():
    line.et_data([],[])
    return line
def animate(i):
    global objlist
    x=[[obj.track[0][j] for j in range(i)] for obj in objlist]
    y=[[obj.track[1][j] for j in range(i)] for obj in objlist]
    line.setdata([],)
anim.FuncAnimation(fig, )