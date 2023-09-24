//
// Created by zhouhb on 23-3-26.
//
#pragma once
#ifndef JLUROBOVISION_CALCULATEFIRINGSOLUTION_H
#define JLUROBOVISION_CALCULATEFIRINGSOLUTION_H


#include "General/General.h"
#include "../Armor/Armor.h"
#include "math.h"
#include <cmath>


class PredictPitch
{
public:
    /*
    * @brief Get Instance
    * 设置成静态函数，保证getInstance及其静态实例在整个程序生命周期内都存在
    * 使用饿汉模式，因为懒汉模式是为调用前省出更多内存而存在的,这里用不着而且有可能出错
    */
    static PredictPitch& getInstance() { return instance; }


    /**
    * @brief Init all parameter
    */
    void InitPredictPitch(float bulletspeednow, double distance,float hrrec);


    /**
    * @brief Set bullet speed
    * @param bulletSpeed: the speed of bullet(m/s)
    */
    double setBulletSpeed(float bulletSpeed);

    /**
    * @brief time model
    */
    double timefd(double v0x, double t1);

    /**
    * @brief angle model
    */
    double anglefd(double t2, double theta);


    /**
    * @brief calculate time
    */
    void time(double v0x, double dr);

    /**
    * @brief calculate angle
    */
    void angle();
    /**
    * @brief used for hero dropshot
   */
    void dropshot();
    /**
    * @brief select algorithm
   */
    double selectalg(double pitch, double distance, float bulletspeednow,float hrrec);



private:
    PredictPitch() {};//把构造函数放在private里面，防止构造函数被外部调用
    double dk, vk, hk, dr;//dk、vk、hk、dr：迭代过程中的距离、速度、高度，与目标的实际距离（注意：长度单位均为m，角度均为角度值）
    double t, theta;//输出的t和角度（角度以弧度制给出）
    double v0,v0x;//发射速度，由从下位机接收到的速度给出
    double hr;//hr:目标高度与枪管的高度差（回头可以再测一下）

    const double k = 0.00556;//阻力系数
    const double dt = 0.0005;//每次仿真计算的步长
    const double g = 9.8;
    const double pi = 3.14159;
    double Y_r;//目标的实际高度
    double a;//风阻带来的加速度
    double Y_d;//枪管的实际高度+迭代
    double theta_d;//用于每次迭代的角度
    double X_r;//目标的实际距离
    double X_d;//枪管的实际长度+迭代
    double lasterr;//pid的上次误差
    double integral;//pid的积分项
    double v0now;//承装迭代时输入的v0
    double v0process;//每次迭代时使用的v0

    static PredictPitch instance;//静态实例全局类共享并会在程序伊始被创建，隐藏在私有中，仅允许public中定义的方法接口去调用
    // 禁止拷贝构造函数和赋值运算符(也就是将它们设置成私有（无法外部使用（也就是只能被其他成员调用了））并不予实现（delete）)，确保单例对象唯一性
    //（爱来自gpt）在C++11之后，我们可以使用delete关键字来显式删除类的特定成员函数，包括构造函数和拷贝构造函数。将这些函数设置为delete意味着在编译时会阻止类外部对这些函数的调用，从而确保单例对象只能通过静态成员函数或静态成员变量获取。
    //不过感觉要是写成返回所定义的静态实例也可以（这样也做到了只存在一个实例）
    PredictPitch(const PredictPitch&) = delete;
    PredictPitch& operator=(const PredictPitch&) = delete;
};

#endif //JLUROBOVISION_CALCULATEFIRINGSOLUTION_H
