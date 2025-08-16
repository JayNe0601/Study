<template>
  <div>
    <div>
      <el-input
          v-model="data.input"
          style="width: 240px"
          placeholder="Type something"
          :prefix-icon="Search"
      />
    </div>
    <div style="margin-top: 10px">
      <el-table :data="data.tableData">
        <el-table-column label="编辑">
          <template #default="scope">
            <el-button type="primary" @click="editContent(scope.row)">
              编辑富文本
            </el-button>
          </template>
        </el-table-column>
        <el-table-column label="ID" prop="id"></el-table-column>
        <el-table-column label="内容" prop="content" show-overflow-tooltip>
          <template #default="scope">
            <div v-html="scope.row.content"></div>
          </template>
        </el-table-column>
        <el-table-column label="时间" prop="time"></el-table-column>

      </el-table>
    </div>
    <el-dialog v-model="data.ContentVisible" :title=data.form.title width="500">
      <div style="padding: 20px">
        <div style="border: 1px solid #ccc; width: 100%">
          <Toolbar
              style="border-bottom: 1px solid #ccc"
              :editor="editorRef"
              :mode="mode"
          />
          <Editor
              style="height: 500px; overflow-y: hidden"
              v-model="data.form.content"
              :model="mode"
              :defaultConfig="editorConfig"
              @onCreated="handleCreated"
          />
        </div>
        <div>
          <el-button type="primary" @click="saveContent">
            保存
          </el-button>
          <el-button type="primary" @click="data.ContentVisible = false">
            取消
          </el-button>
        </div>
      </div>
    </el-dialog>
  </div>
</template>

<script setup>

import { reactive, onBeforeUnmount, ref, shallowRef } from "vue";
import { Search } from '@element-plus/icons-vue'
import request from "@/utils/request.js";
import '@wangeditor/editor/dist/css/style.css'; // 引入 CSS
import { Editor, Toolbar } from "@wangeditor/editor-for-vue"
import {ElMessage} from "element-plus";

const data = reactive({
  input: '',
  employees: [],
  tableData: [],
  ContentVisible: false,
  form: {},
})

const load = () => {
  request.get('/article/selectAll').then(res => {
    // .list 是因为后端处理时返回的是 list
    data.tableData = res.data
  })
}
load()

const baseUrl = 'http://localhost:9090'
const editorRef = shallowRef()
const mode = 'default'
const editorConfig = {MENU_CONF: {}}
// 图片上传配置
editorConfig.MENU_CONF['uploadImage'] = {
  // 服务端图片上传接口
  server: baseUrl + '/files/wang/upload',
  // 服务端图片上传接口参数
  fieldName: 'file'
}
// 组件销毁时，也及时销毁编辑器，否则可能造成内存泄露
onBeforeUnmount(() => {
  const editor = editorRef.value
  if (editor == null) return
  editor.destroy()
})
// 记录 editor 实例
const handleCreated = (editor) => {
  editorRef.value = editor
}

const editContent = (row) => {
  data.ContentVisible = true
  data.form = row
}

const saveContent = () => {
  request.put('/article/update', data.form).then(res => {
    if (res.code === '200') {
      ElMessage.success("操作成功")
      load() // 新增后要重新加载最新数据
    } else {
      ElMessage.error(res.msg)
    }
  })
  data.ContentVisible = false
}


</script>