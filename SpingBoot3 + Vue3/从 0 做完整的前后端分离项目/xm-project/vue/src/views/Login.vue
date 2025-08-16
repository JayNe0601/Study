<template>
  <div class="login-container">
    <div class="login-box">
      <div style="padding: 20px; background-color: white; margin-left: 100px">
        <div style="margin-bottom: 30px; font-size: 24px; color: #0089ff; font-weight: bold; text-align: center">
          欢迎登录后台管理系统
        </div>
        <el-form ref="formRef" :rules="data.rules" :model="data.form" style="width: 350px;">
          <el-form-item label="账 号" prop="username">
            <el-input v-model="data.form.username" placeholder="请输入账号"></el-input>
          </el-form-item>
          <el-form-item label="密 码" prop="password">
            <el-input show-password v-model="data.form.password" placeholder="请输入密码"></el-input>
          </el-form-item>
          <div style="margin-bottom: 20px">
            <el-button style="width: 100%" type="primary" @click="login">
              登 录
            </el-button>
          </div>
          <div>
            还没有账号？请<a href="/register">注册</a>
          </div>
        </el-form>
      </div>

    </div>
  </div>
</template>

<script setup>
import { reactive, ref } from "vue";
import request from "@/utils/request.js";
import {ElMessage} from "element-plus";

const data = reactive({
  form: {},
  rules: {
    username: [
      { required: true, message: "请输入账号", trigger: "blur" }
    ],
    password: [
      { required: true, message: "请输入密码", trigger: "blur" }
    ]
  }
})

const formRef = ref()

const login = () => {
  formRef.value.validate((valid) => {
    if (valid) {
      request.post("/login", data.form).then(res => {
        if(res.code === '200') {
          // 存储后台返回的信息（注意：这个只能存字符串）
          localStorage.setItem('xm-project-user', JSON.stringify(res.data)) // 把 json 对象转换成 json 字符串
          ElMessage.success('登陆成功');
          location.href = '/manager/home'
        }
        else {
          ElMessage.error(res.msg)
        }
      })
    }
  })
}

</script>

<style scoped>
.login-container {
  width: 100%;
  height: 100vh;
  overflow: hidden;
  background-image:url("../assets/bg.png");
  background-size: cover;
}

.login-box {
  width: 40%;
  height: 80%;
  right: 30%;
  left: 30%;
  top: 10%;
  position: absolute;
  display: flex;
  align-items: center;
}
</style>