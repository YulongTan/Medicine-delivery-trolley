/*
 * PID.c
 *
 *  Created on: 2023年5月25日
 *      Author: lenovo
 */
#include"PID.h"
struct gesture gest;//当前姿态
struct gesture tgest;//目标姿态
struct gesture globalgest;//初始姿态
struct pidstruct angrpid;//角度PID
struct pidstruct angxpid;//x轴角度PID
struct pidstruct angypid;
struct pidstruct angzpid;
struct pidstruct x1pid;//位移PID
struct pidstruct x2pid;
struct pidstruct v1pid;
struct pidstruct v2pid;
extern struct pidstruct initPID(float kp, float ki, float kd, struct pidstruct e)//初始化PID
{
    e.kp=kp;
    e.ki=ki;
    e.kd=kd;
    e.p=0;//有必要时不用初始化给0
    e.i=0;
    e.d=0;
    e.lastde =0;
    e.thisde=0;
    return e;
}
extern float PID(struct pidstruct *e,float err, float outhigh , float outlow)//返回PID的值 outhigh和outlow是限幅
{
    float out;
    e->thisde=err;
    e->p = e->kp * e->thisde ;
    e->i = e->ki * (e->i+e->lastde );
    e->d = e->kd * (e->thisde -e->lastde );
    e->lastde = e->thisde ;
    out=e->p+e->i +e->d;
    if(out>outhigh ) out=outhigh ;//限幅
    if(out<outlow ) out =outlow ;
    return out;
}


