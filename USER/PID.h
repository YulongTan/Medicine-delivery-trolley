/*
 * PID.h
 *
 *  Created on: 2023年5月25日
 *      Author: lenovo
 */

#ifndef USER_PID_H_
#define USER_PID_H_
struct gesture
{
    float angr;//角度
    float angx;
    float angy;
    float w;//角速度
    float v1;//左轮速度
    float v2;//右轮速度
//    unsigned long v1;//左轮速度
//    unsigned long v2;//右轮速度
//    long v1;
//    long v2;
    float x1;//左轮位移
    float x2;//右轮位移
    float x;//总位移
};
struct pidstruct
{
    float kp,ki,kd;
    float p ,i ,d;
    float thisde, lastde;
};  //thisde当前
extern struct gesture gest;//当前姿态
extern struct gesture tgest;//目标姿态
extern struct gesture globalgest;//初始姿态
extern struct pidstruct angrpid;//角度PID
extern struct pidstruct angxpid;//x轴角度PID
extern struct pidstruct angypid;
extern struct pidstruct angzpid;
extern struct pidstruct x1pid;//位移PID
extern struct pidstruct x2pid;
extern struct pidstruct v1pid;
extern struct pidstruct v2pid;
extern struct pidstruct initPID(float kp, float ki, float kd, struct pidstruct e);//初始化PID
extern float PID(struct pidstruct *e,float err, float outhigh , float outlow);


#endif /* USER_PID_H_ */
