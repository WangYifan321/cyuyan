<template>
  <div style="text-align: center">
<h1>杭电外来人员登记</h1>
    <h1>担保人审批系统</h1>
    <el-collapse v-model="activeNames" @change="handleChange" style="width: 90%;margin-left: auto;margin-right: auto">
      <el-collapse-item title="张三" name="1" v-if="flag">
        <div style="margin-left: 20px;text-align: left">
          <p>申请人联系方式：12881292101</p>
          <p>申请原因：吃饭</p>
          <p>14天内是否去过疫区：否</p>
          <p>健康码：绿</p>
          <p>是否有感冒发烧等症状：是</p>
          <p>进校时间：2021-12-02 21:09</p>
          <p>离校时间：2021-12-02 21:10</p>
          <p>申请原因：我要吃饭</p>
          <p>单位信息：我要吃饭</p>
         <el-button style="background-color: #0066ff;color: white" @click="agree()">同意</el-button>
          <el-button style="background-color: #0066ff;color: white;margin-left: 100px" @click="refuse()">拒绝</el-button>
        </div>
      </el-collapse-item>
      <el-collapse-item title="李四" name="2">
        <div style="margin-left: 20px;text-align: left">
          <p>申请人联系方式：12881292101</p>
          <p>申请原因：吃饭</p>
          <p>14天内是否去过疫区：否</p>
          <p>健康码：绿</p>
          <p>是否有感冒发烧等症状：是</p>
          <p>进校时间：2021-12-02 21:09</p>
          <p>离校时间：2021-12-02 21:10</p>
          <p>申请原因：我要吃饭</p>
          <p>单位信息：我要吃饭</p>
          <el-button style="background-color: #0066ff;color: white">同意</el-button>
          <el-button style="background-color: #0066ff;color: white;margin-left: 100px">拒绝</el-button>
        </div>
      </el-collapse-item>
      <el-collapse-item title="王五" name="3">
        <div style="margin-left: 20px;text-align: left">
          <p>申请人联系方式：12881292101</p>
          <p>申请原因：吃饭</p>
          <p>14天内是否去过疫区：否</p>
          <p>健康码：绿</p>
          <p>是否有感冒发烧等症状：是</p>
          <p>进校时间：2021-12-02 21:09</p>
          <p>离校时间：2021-12-02 21:10</p>
          <p>申请原因：我要吃饭</p>
          <p>单位信息：我要吃饭</p>
          <el-button style="background-color: #0066ff;color: white">同意</el-button>
          <el-button style="background-color: #0066ff;color: white;margin-left: 100px">拒绝</el-button>
        </div>
      </el-collapse-item>
      <el-collapse-item title="李斌" name="4">
        <div style="margin-left: 20px;text-align: left">
          <p>申请人联系方式：12881292101</p>
          <p>申请原因：吃饭</p>
          <p>14天内是否去过疫区：否</p>
          <p>健康码：绿</p>
          <p>是否有感冒发烧等症状：是</p>
          <p>进校时间：2021-12-02 21:09</p>
          <p>离校时间：2021-12-02 21:10</p>
          <p>申请原因：我要吃饭</p>
          <p>单位信息：我要吃饭</p>
          <el-button style="background-color: #0066ff;color: white">同意</el-button>
          <el-button style="background-color: #0066ff;color: white;margin-left: 100px">拒绝</el-button>
        </div>
      </el-collapse-item>
    </el-collapse>
  </div>
</template>

<script>
export default {
  name: "guarantee_index",
  data() {
    return {
      flag: true,
      activeNames: ['1']
    };
  },
  methods: {
    handleChange(val) {
      console.log(val);
    },
    agree() {
      this.$confirm('此操作将同意此人入校，您为担保人, 是否继续?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).then(() => {
        this.$message({
          type: 'success',
          message: '成功!',
        });
        this.flag = false
      }).catch(() => {
        this.$message({
          type: 'info',
          message: '已取消'
        });
      });
    }
  }
}
</script>

<style >
.el-message-box{
  width: 90% !important;
}
</style>
