/*
 * PID.h
 *
 *  Created on: 2023��5��25��
 *      Author: lenovo
 */

#ifndef USER_PID_H_
#define USER_PID_H_
struct gesture
{
    float angr;//�Ƕ�
    float angx;
    float angy;
    float w;//���ٶ�
    float v1;//�����ٶ�
    float v2;//�����ٶ�
//    unsigned long v1;//�����ٶ�
//    unsigned long v2;//�����ٶ�
//    long v1;
//    long v2;
    float x1;//����λ��
    float x2;//����λ��
    float x;//��λ��
};
struct pidstruct
{
    float kp,ki,kd;
    float p ,i ,d;
    float thisde, lastde;
};  //thisde��ǰ
extern struct gesture gest;//��ǰ��̬
extern struct gesture tgest;//Ŀ����̬
extern struct gesture globalgest;//��ʼ��̬
extern struct pidstruct angrpid;//�Ƕ�PID
extern struct pidstruct angxpid;//x��Ƕ�PID
extern struct pidstruct angypid;
extern struct pidstruct angzpid;
extern struct pidstruct x1pid;//λ��PID
extern struct pidstruct x2pid;
extern struct pidstruct v1pid;
extern struct pidstruct v2pid;
extern struct pidstruct initPID(float kp, float ki, float kd, struct pidstruct e);//��ʼ��PID
extern float PID(struct pidstruct *e,float err, float outhigh , float outlow);


#endif /* USER_PID_H_ */
