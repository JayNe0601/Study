<template>
  <div>
    <el-card style="max-width: 480px">
      <div style="padding: 10px">
        <el-form ref="formRef" :rules="data.rules" :model="data.form" label-width="80px">
          <el-form-item label="原密码" prop="password">
            <el-input show-password v-model="data.form.password"
                      autocomplete="off" placeholder="请输入原密码"/>
          </el-form-item>
          <el-form-item label="新密码" prop="newPassword">
            <el-input show-password v-model="data.form.newPassword"
                      autocomplete="off" placeholder="请输入新密码"/>
          </el-form-item>
          <el-form-item label="确认密码" prop="confirmPassword">
            <el-input show-password v-model="data.form.confirmPassword"
                      autocomplete="off" placeholder="请确认新密码"/>
          </el-form-item>
          <div style="text-align: center">
            <el-button type="primary"
                       @click="updatePassword" style="padding: 20px">
              修 改
            </el-button>
          </div>
        </el-form>
      </div>
    </el-card>
  </div>
</template>

<script setup>

import { ref, reactive } from "vue";
import request from "@/utils/request.js";
import {ElMessage} from "element-plus";

const validatePass = (rule, value, callback) => {
  if (!value) {
    callback(new Error('请再次确认密码'))
  } else if (value !== data.form.newPassword) {
    callback(new Error("两次输入密码不一致"))
  } else {
    callback()
  }
}


const data = reactive({
  user: JSON.parse(localStorage.getItem("xm-project-user")),
  form: {},
  rules: {
    password: [
      { required: true, message: "请输入原密码", trigger: "blur" }
    ],
    newPassword: [
      { required: true, message: "请输入新密码", trigger: "blur" }
    ],
    confirmPassword: [
      { validator: validatePass, trigger: "blur" }
    ]
  }
})

const formRef = ref()

const updatePassword = () => {
  formRef.value.validate((valid) => {
    if (valid) {
      data.form.id = data.user.id
      request.put("/updatePassword", data.form).then(res => {
        if(res.code === '200') {
          ElMessage.success('修改成功')
          localStorage.removeItem('xm-project-user');
          // 设置延迟(500 ms)退出
          setTimeout(() => {
            location.href = '/Login'
          }, 500)
        }
        else {
          ElMessage.error(res.msg)
        }
      })
    }
  })
}

</script>