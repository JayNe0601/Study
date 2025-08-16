<template>
  <dic>
    <el-card style="max-width: 480px">
      <div style="padding: 10px">
        <el-form :model="data.form" label-width="80px">
          <el-form-item label="头像">
            <el-upload
                class="avatar-uploader"
                action="http://localhost:9090/files/upload"
                :show-file-list="false"
                :on-success="handleAvatarSuccess"
            >
              <img v-if="data.form.avatar" :src="data.form.avatar"
                   class="avatar" />
              <el-icon v-else class="avatar-uploader-icon">
                <Plus />
              </el-icon>
            </el-upload>
            <el-button type="primary" @click="downloadAvatar" style="padding: 5px;" >
              下载图片
            </el-button>
          </el-form-item>

          <el-form-item label="账号">
            <el-input disabled v-model="data.form.username"
                      autocomplete="off" />
          </el-form-item>
          <el-form-item label="名称">
            <el-input v-model="data.form.name"
                      autocomplete="off" />
          </el-form-item>
          <div v-if="data.user.role === 'EMP'">
            <el-form-item label="性别">
              <el-radio-group v-model="data.form.sex">
                <el-radio value="男" label="男"></el-radio>
                <el-radio value="女" label="女"></el-radio>
              </el-radio-group>
            </el-form-item>
            <el-form-item label="工号">
              <el-input v-model="data.form.no"
                        placeholder="请输入工号"
                        autocomplete="off"/>
            </el-form-item>
            <el-form-item label="年龄">
              <el-input-number style="width: 100px"
                               min="18"
                               v-model="data.form.age"
                               autocomplete="off" />
            </el-form-item>
            <el-form-item label="个人介绍">
              <el-input type="textarea"
                        v-model="data.form.descr"
                        autocomplete="off" />
            </el-form-item>
          </div>

          <div style="text-align: center">
            <el-button type="primary"
                      @click="updateUser" style="padding: 20px">
              更新个人信息
            </el-button>
          </div>
        </el-form>
      </div>
    </el-card>
  </dic>

</template>

<script setup>
import { reactive, ref } from "vue";
import request from "@/utils/request.js";
import {ElMessage} from "element-plus";
import { Plus } from "@element-plus/icons-vue";


const data = reactive({
  user: JSON.parse(localStorage.getItem("xm-project-user")),
  form: {}
})

const emit = defineEmits(['UpdateUser'])

data.form = data.user

const updateUser = () => {
  request.put('/employee/update', data.form).then(res => {
    if(res.code === '200') {
      ElMessage.success("更新成功")
      // 更新缓存数据
      localStorage.setItem("xm-project-user", JSON.stringify(data.form))
      emit('UpdateUser')
    } else {
      ElMessage.error(res.msg)
    }
  })
}

const handleAvatarSuccess = (res) => {
  data.form.avatar = res.data
}

const downloadAvatar = () => {
  if(data.form.avator) {
    location.href = data.form.avatar
  }
  else {
    ElMessage.error("没用头像不可下载")
  }
}

</script>

<style scoped>
.avatar-uploader .avatar {
  width: 170px;
  height: 170px;
  display: block;
}
</style>

<style>
.avatar-uploader .el-upload {
  border: 1px dashed var(--el-border-color);
  border-radius: 6px;
  cursor: pointer;
  position: relative;
  overflow: hidden;
  transition: var(--el-transition-duration-fast);
}

.avatar-uploader .el-upload:hover {
  border-color: var(--el-color-primary);
}

.el-icon.avatar-uploader-icon {
  font-size: 28px;
  color: #8c939d;
  width: 170px;
  height: 170px;
  text-align: center;
}
</style>