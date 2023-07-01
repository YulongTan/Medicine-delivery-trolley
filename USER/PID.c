/*
 * PID.c
 *
 *  Created on: 2023��5��25��
 *      Author: lenovo
 */
#include"PID.h"
struct gesture gest;//��ǰ��̬
struct gesture tgest;//Ŀ����̬
struct gesture globalgest;//��ʼ��̬
struct pidstruct angrpid;//�Ƕ�PID
struct pidstruct angxpid;//x��Ƕ�PID
struct pidstruct angypid;
struct pidstruct angzpid;
struct pidstruct x1pid;//λ��PID
struct pidstruct x2pid;
struct pidstruct v1pid;
struct pidstruct v2pid;
extern struct pidstruct initPID(float kp, float ki, float kd, struct pidstruct e)//��ʼ��PID
{
    e.kp=kp;
    e.ki=ki;
    e.kd=kd;
    e.p=0;//�б�Ҫʱ���ó�ʼ����0
    e.i=0;
    e.d=0;
    e.lastde =0;
    e.thisde=0;
    return e;
}
extern float PID(struct pidstruct *e,float err, float outhigh , float outlow)//����PID��ֵ outhigh��outlow���޷�
{
    float out;
    e->thisde=err;
    e->p = e->kp * e->thisde ;
    e->i = e->ki * (e->i+e->lastde );
    e->d = e->kd * (e->thisde -e->lastde );
    e->lastde = e->thisde ;
    out=e->p+e->i +e->d;
    if(out>outhigh ) out=outhigh ;//�޷�
    if(out<outlow ) out =outlow ;
    return out;
}


