<template>
  <div>
    <div style="margin-bottom: 10px">
      <el-card> <!-- 卡片 -->
        <el-input
            v-model="data.name"
            style="width: 240px; margin-right: 10px"
            placeholder="请输入名称查询"
            :prefix-icon="Search"
        />
        <el-button type="primary" @click="load">
          查 询
        </el-button>
        <el-button type="primary" @click="reset">
          重 置
        </el-button>
      </el-card>
    </div>
    <div style="margin-bottom: 10px">
      <el-card>
        <el-button type="primary" @click="handleAdd">
          新增
        </el-button>
        <el-button type="primary" @click="delBatch">
          批量删除
        </el-button>
      </el-card>
    </div>
    <div>
      <el-card>
        <el-table :data="data.tableData" stripe
                  @selection-change="handleSelectionChange">
          <el-table-column type="selection" width="55" />
          <el-table-column label="头像">
            <template #default="scope">

              <img v-if="scope.row.avatar" :src="scope.row.avatar" alt="" style="width: 40px; height: 40px; border-radius: 50%"/>
            </template>
          </el-table-column>
          <el-table-column label="账号" prop="username" />
          <el-table-column label="员工ID" prop="id" />
          <el-table-column label="名称" prop="name" />
          <el-table-column label="性别" prop="sex" />
          <el-table-column label="工号" prop="no" />
          <el-table-column label="年龄" prop="age" />
          <el-table-column label="个人介绍" prop="descr" show-overflow-tooltip />
          <el-table-column label="操作">
            <template #default="scope">
              <el-button type="primary"
                         @click="handleUpdate(scope.row)">
                edit
              </el-button>
              <el-button type="primary"
                         @click="Delete(scope.row.id)">
                delete
              </el-button>
            </template>
          </el-table-column>
          <!-- 与部门id关联，后续补充-->
        </el-table>
        <div style="margin-top: 10px">
          <el-pagination
              @change="load"
              v-model:current-page="data.pageNum"
              v-model:page-size="data.pageSize"
              :page-Size="[5, 10, 15, 20]"
              background
              layout="total, sizes, prev, pager, next, jumper"
              :total="data.total"
          />
        </div>
      </el-card>
    </div>

      <el-dialog title="员工信息"
                 v-model="data.formVisible" width="500">
        <el-form :model="data.form" label-width="80px">
          <el-form-item label="账号">
            <el-input v-model="data.form.username"
                      autocomplete="off" />
          </el-form-item>
          <el-form-item label="头像" >
            <el-upload
                action="http://localhost:9090/files/upload"
                list-type="picture"
                :on-success="handleAvatarSuccess"
                :show-file-list=flag
                :limit=1
                v-model:file-list="data.fileList"
            >
              <el-button>上传头像</el-button>
            </el-upload>
          </el-form-item>
          <el-form-item label="名称">
            <el-input v-model="data.form.name"
                      autocomplete="off" />
          </el-form-item>
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
        </el-form>
        <template #footer>
          <div class="dialog-footer">
            <el-button @click="cancel">
              取 消
            </el-button>
            <el-button type="primary" @click="save">
              保 存
            </el-button>
          </div>
        </template>
      </el-dialog>

  </div>
</template>

<script setup>

import {reactive,ref} from "vue";
import request from "@/utils/request.js";
import {ElMessage, ElMessageBox} from "element-plus";
import {Plus} from "@element-plus/icons-vue";

const data = reactive({
  name: '',
  tableData: [],
  pageNum: 1,
  pageSize: 10,
  total: 100,
  formVisible: false,
  form: {},
  id: [],
  fileList: []
})
const flag = ref(true);

const load = () => {
  // 是这个类型的：?pageNum=1&pageSize=10
  // 通过 params 传递参数值
  request.get('/employee/selectPage',{
    params: {
      pageNum: data.pageNum,
      pageSize: data.pageSize,
      name: data.name
    }
  }).then(res => {
    // .list 是因为后端处理时返回的是 list
    data.tableData = res.data.list
    // 设置总值
    data.total = res.data.total
  })
}

const reset = () => {
  data.name = null
  load()
}

const handleAdd = () => {
  data.formVisible = true
  data.form = {}
}

const save = () => {
  // 在一个 save 里面做两种操作，
  // 一个新增，一个编辑
  // 新增时未输入 id，而编辑的 from 里面有 id
  flag.value = false
  data.form.id ? update() : add()
  data.fileList = []
}

const update = () => {
  request.put('/employee/update', data.form).then(res => {
    if (res.code === '200') {
      ElMessage.success("操作成功")
      load() // 新增后要重新加载最新数据
    } else {
      ElMessage.error(res.msg)
    }
  })
  data.formVisible = false
}

const add = () => {
  request.post('/employee/add', data.form).then(res => {
    if (res.code === '200') {
      ElMessage.success("操作成功")
      load() // 新增后要重新加载最新数据
    } else {
      ElMessage.error(res.msg)
    }
  })
  data.formVisible = false
}

const handleUpdate = (row) => {
  // row 是行对象，若直接这样写
  // 那么修改后未保存也显示的会是修改后的值
  // 但数据库未改变
  // data.form = row
  // 应该用 JSON 深拷贝一个新的对象，
  // 用于编辑，这样就不会影响行对象
  data.form = JSON.parse(JSON.stringify(row))
  data.formVisible = true
}

const Delete = (id) => {
  ElMessageBox.confirm('删除后无法恢复，您确认删除信息吗？',
      '删除确认',
      {type: 'warning'}).then(() => {
    request.delete('/employee/deleteById/' + id).then(res => {
      if (res.code === '200') {
        ElMessage.success("删除成功")
        load()//  删除后要重新加载最新数据
      }
      else {
        ElMessage.error(res.msg)
      }
    })
  }).catch()
}

const handleSelectionChange = (rows) => {
  // 从选择的行数组里面取出所有行的 id
  // 组成的一个新的数组，通过 map 来处理
  data.ids = rows.map(rows => rows.id)
}

const delBatch = () => {
  if(data.ids.length === 0) {
    ElMessage.warning("请选择数据")
  }
  ElMessageBox.confirm('删除后无法恢复，您确认删除信息吗？',
      '删除确认',
      {type: 'warning'}).then(() => {
    request.delete('/employee/deleteBatch',
        {data: data.ids}).then(res => {
      if (res.code === '200') {
        ElMessage.success("删除成功")
        load()
      }
      else {
        ElMessage.error(res.msg)
      }
    })
  }).catch()
}

const handleAvatarSuccess = (res) => {
  flag.value = true
  data.form.avatar = res.data
}

const cancel = () => {
  data.formVisible = false
  data.fileList = []
  data.flag = false
}

// 调用 load()
load()
</script>