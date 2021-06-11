<template>
  <div style="text-align: center">
<h1>杭电外来人员登记</h1>
    <h1>担保人审批系统</h1>
    <el-collapse v-model="activeNames" @change="handleChange" style="width: 90%;margin-left: auto;margin-right: auto">
      <el-collapse-item v-for="(outsider,i) in info" :key="i"  :title=outsider.name name="1" >
        <div style="margin-left: 20px;text-align: left">
          <p>姓名：{{outsider.name}}</p>
          <p>申请人联系方式：{{outsider.phone}}</p>
          <p>申请原因：{{outsider.cause}}</p>
          <p>14天内是否去过疫区：{{outsider.affected}}</p>
          <p>健康码：绿</p>
          <p>是否有感冒发烧等症状：是</p>
          <p>进校时间：{{outsider.apply_entry}}</p>
          <p>离校时间：{{outsider.apply_leave}}</p>
          <p>单位信息：{{outsider.unit_info}}</p>
         <el-button style="background-color: #0066ff;color: white" @click="agree(outsider.id)">同意</el-button>
          <el-button style="background-color: #0066ff;color: white;margin-left: 100px" @click="refuse(outsider.id)">拒绝</el-button>
        </div>
      </el-collapse-item>


    </el-collapse>
  </div>
</template>

<script>
import {guarantee_get_outsiders} from "../apis/api";
import {update_pass1} from "../apis/api";
import {update_pass2} from "../apis/api";

export default {
  name: "guarantee_index",
  data() {
    return {
      flag: true,
      activeNames: ['1'],
      info: []
    };
  },
  methods: {
    handleChange(val) {
      console.log(val);
    },
    agree(id) {
      this.$confirm('此操作将同意此人入校，您为担保人, 是否继续?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).then(() => {
        this.$message({
          type: 'success',
          message: '成功!',
        });
       let url = 'apis/outsiders/'+id+'/pass'
        let params = {}
        update_pass1(url,params).then(res =>{
          this.$router.go(0)
        })
      }).catch(() => {
        this.$message({
          type: 'info',
          message: '已取消'
        });
      });
    },
    refuse(id) {
      this.$confirm('此操作将拒绝此人入校, 是否继续?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).then(() => {
        this.$message({
          type: 'success',
          message: '成功!',
        });
        let url = 'apis/outsiders/'+id+'/nopass'
        let params = {}
        update_pass1(url,params).then(res =>{
          this.$router.go(0)
        })
      }).catch(() => {
        this.$message({
          type: 'info',
          message: '已取消'
        });
      });
    },
    getData(){
      let params = {}
      guarantee_get_outsiders(params).then(res => {
        this.info = res
      })
    }
  },
  mounted() {
    this.getData()
  }
}
</script>

<style >
.el-message-box{
  width: 90% !important;
}
</style>
