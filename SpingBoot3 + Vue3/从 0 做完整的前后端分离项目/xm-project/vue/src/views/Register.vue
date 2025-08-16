<template>
  <div class="login-container">
    <div class="login-box">
      <div style="padding: 20px; background-color: white; margin-left: 100px">
        <div style="margin-bottom: 30px; font-size: 24px; color: #0089ff; font-weight: bold; text-align: center">
          欢迎注册
        </div>
        <el-form ref="formRef" :rules="data.rules" :model="data.form" style="width: 350px;">
          <el-form-item label="账 号" prop="username">
            <el-input v-model="data.form.username" placeholder="请输入账号"></el-input>
          </el-form-item>
          <el-form-item label="密 码" prop="password">
            <el-input show-password v-model="data.form.password" placeholder="请输入密码"></el-input>
          </el-form-item>
          <el-form-item label="确 认 密 码" prop="confirmPassword">
            <el-input show-password v-model="data.form.confirmPassword" placeholder="请确认密码"></el-input>
          </el-form-item>
          <div style="margin-bottom: 20px">
            <el-button style="width: 100%" type="primary" @click="register">
              注 册
            </el-button>
          </div>
          <div>
            已有账号？请<a href="/Login">登录</a>
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

const validatePass = (rule, value, callback) => {
  if (!value) {
    callback(new Error('请再次确认密码'))
  } else if (value !== data.form.password) {
    callback(new Error("两次输入密码不一致"))
  } else {
    callback()
  }
}

const data = reactive({
  form: {},
  rules: {
    username: [
      { required: true, message: "请输入账号", trigger: "blur" }
    ],
    password: [
      { required: true, message: "请输入密码", trigger: "blur" }
    ],
    confirmPassword: [
      { validator: validatePass, trigger: "blur" }
    ]
  }
})

const formRef = ref()

const register = () => {
  formRef.value.validate((valid) => {
    if (valid) {
      request.post("/register", data.form).then(res => {
        if(res.code === '200') {
          ElMessage.success('注册成功');
          location.href = '/login'
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