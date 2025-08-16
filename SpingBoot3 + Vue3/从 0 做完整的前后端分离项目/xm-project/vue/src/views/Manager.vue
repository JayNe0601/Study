<template>

  <div>
        <!-- 头部开始 -->
        <div style="height: 60px; background-color: #0089ff; display: flex; align-items: center">
            <div style="width: 200px; align-items: center;">
                <img style="width: 40px; margin-right: 5px" src="../assets/logo.png">
                <span style="font-size: 20px; color: white">后台管理系统</span>
            </div>
            <div style="flex: 1"></div>
            <div style="width: 150px; display: flex; align-items: center">
                <img :src="data.user.avatar || state.circleUrl" alt="" style="width: 40px; height: 40px; border-radius: 50%">
                <span style="color: white; margin-left: 5px">{{data.user.name}}</span>
            </div>
        </div>
        <!-- 头部结束 -->

        <!-- 下面部分开始 -->
        <!-- 包括导航菜单和数据展示区域 -->
        <div style="display: flex">
            <!-- 导航菜单开始 -->
            <!-- 导航菜单，可以在element官网里面找 -->
            <div style="width: 150px; border-right: 1px solid #ddd; min-height: calc(100vh - 60px)">
                <el-menu router :default-active="router.currentRoute.value.path" style="border: 0">
                    <el-menu-item index="/manager/home">
                        <el-icon><House /></el-icon>
                        系统首页
                    </el-menu-item>
                    <el-menu-item index="/manager/data">
                        <el-icon><DataAnalysis /></el-icon>
                        数据统计
                    </el-menu-item>
                    <el-sub-menu index="1">
                        <template #title>
                            <!-- 用户管理前面添加图表 -->
                            <el-icon><User /></el-icon>
                            <span>用户管理</span>
                        </template>
                        <el-menu-item>管理员信息</el-menu-item>
                        <el-menu-item index="/manager/employee">企业员工信息</el-menu-item>
                    </el-sub-menu>
                    <el-menu-item index="/manager/person">
                        <el-icon><UserFilled /></el-icon>
                        <spon>个人信息</spon>
                    </el-menu-item>
                    <el-menu-item index="/manager/password">
                        <el-icon><Lock /></el-icon>
                        <spon>修改密码</spon>
                    </el-menu-item>
                    <el-menu-item @click="logout">
                        <el-icon><SwitchButton /></el-icon>
                        <spon>退出登录</spon>
                    </el-menu-item>
                </el-menu>
            </div>
            <!-- 导航菜单结束 -->
            <!-- 数据展示区域开始 -->
            <div style="flex: 1; width: 0; background-color: #e3effc; padding: 10px">
                <RouterView @UpdateUser="updateUser"/>
            </div>
            <!-- 数据展示区域结束 -->
        </div>
        <!-- 下面部分结束 -->
    </div>
</template>

<script setup>
import {reactive} from "vue";
import router from "@/router/index.js";
const state = reactive({
    circleUrl: 'https://cube.elemecdn.com/3/7c/3ea6beec64369c2642b92c6726f1epng.png',
})

const data = reactive({
  user: JSON.parse(localStorage.getItem('xm-project-user')),
})

const logout = () => {
  localStorage.removeItem('xm-project-user');
  location.href = '/Login';
}

const updateUser = () => {
  data.user = JSON.parse(localStorage.getItem('xm-project-user'));
}

</script>

<style>
/*背景可以始终高亮*/
.el-menu .is-active {
    background-color: #e6ecf7 !important;
}
</style>