<template>


    <el-form ref="myForm" :model="myForm" label-width="80px" label-position="top"  style="margin-left: 15px">
      <el-form-item label="姓名">
        <el-input v-model="myForm.name"></el-input>
      </el-form-item>
      <el-form-item label="性别">
        <el-select v-model="myForm.gender" placeholder="请选择性别">
          <el-option label="男" value="1"></el-option>
          <el-option label="女" value="0"></el-option>
        </el-select>
      </el-form-item>
      <el-form-item label="联系方式">
        <el-input v-model="myForm.phone"></el-input>
      </el-form-item>
      <el-form-item label="身份证号">
        <el-input v-model="myForm.ID_card"></el-input>
      </el-form-item>
      <el-form-item label="车牌号">
        <el-input v-model="myForm.car_num" placeholder="不开车不需要填写"></el-input>
      </el-form-item>
      <el-form-item label="担保人姓名">
        <el-input v-model="myForm.guarantor_name"></el-input>
      </el-form-item>
      <el-form-item label="担保人ID">
        <el-input v-model="myForm.guarantor_id" placeholder="学号或职工号"></el-input>
      </el-form-item>
      <el-form-item label="申请进入时间">
        <el-col :span="11">
          <el-date-picker type="date" placeholder="选择日期" v-model="myForm.apply_entry" style="width: 100%;"></el-date-picker>
        </el-col>
        <el-col class="line" :span="2">-</el-col>
        <el-col :span="11">
          <el-time-picker placeholder="选择时间" v-model="myForm.apply_entry" style="width: 100%;"></el-time-picker>
        </el-col>
      </el-form-item>
      <el-form-item label="预计离开时间">
        <el-col :span="11">
          <el-date-picker type="date" placeholder="选择日期" v-model="myForm.apply_leave" style="width: 100%;"></el-date-picker>
        </el-col>
        <el-col class="line" :span="2">-</el-col>
        <el-col :span="11">
          <el-time-picker placeholder="选择时间" v-model="myForm.apply_leave" style="width: 100%;"></el-time-picker>
        </el-col>
      </el-form-item>
      <el-form-item label="14天是否去过疫区">
        <el-radio-group v-model="myForm.affected">
          <el-radio label="1" >是</el-radio>
          <el-radio label="0">否</el-radio>
        </el-radio-group>
      </el-form-item>
      <el-form-item label="是否有感冒发烧等症状">
        <el-radio-group v-model="myForm.cough">
          <el-radio label="1">是</el-radio>
          <el-radio label="0">否</el-radio>
        </el-radio-group>
      </el-form-item>
      <el-form-item label="健康码">
        <el-radio-group v-model="myForm.health_code">
          <el-radio label="1">绿</el-radio>
          <el-radio label="0">非绿</el-radio>
        </el-radio-group>
      </el-form-item>
      <el-form-item label="单位信息">
        <el-input type="textarea" v-model="myForm.unit_info"></el-input>
      </el-form-item>
      <el-form-item label="申请事由">
        <el-input type="textarea" v-model="myForm.cause"></el-input>
      </el-form-item>
      <el-form-item>
        <el-button type="primary" @click="submitForm()">立即申请</el-button>
      </el-form-item>
    </el-form>
</template>

<script>
import {submitForm} from "../apis/api";
import qs from "qs"

export default {
  name: "userForm",
  data() {
    return {
      myForm: {
        name: '',
        gender: '',
        phone: '',
        ID_card: '',
        unit_info: '',
        car_num: '',
        cause: '',
        guarantor_name: '',
        guarantor_id: '',
        health_code: '',
        affected: '',
        cough: '',
        apply_entry: '',
        apply_leave: '',
      }
    }
  },
  methods: {
      submitForm(){
        console.log('kk')
        submitForm(qs.stringify(this.myForm)).then(res => {
          console.log(res)
        })
      },
      insert(){
        let flag = 9
        while(flag--){
          this.myForm.ID_card = '12345678972054321'+flag
          this.myForm.guarantor_id = '19061529'
          this.myForm.guarantor_name = '李品成'
          this.myForm.cause = '我要学习啊'
          this.myForm.name = '李哈哈' + flag
          this.myForm.affected = 0
          this.myForm.health_code = 1
          this.myForm.car_num = 123+flag
          this.myForm.cough = 0
          this.myForm.unit_info = flag
          this.myForm.phone = '1395643191'+flag
          this.myForm.gender = 1;
          this.myForm.apply_entry = '2021-01-2'+flag+'T16:00:00.000Z'
          this.myForm.apply_leave = '2021-02-2'+flag+'T16:00:00.000Z'
          submitForm(qs.stringify(this.myForm)).then(res => {
            console.log(res)
          })

        }
      }
  },
  mounted() {
    this.insert()
  }
}
</script>

<style scoped>
/deep/ .el-form-item__label{
  font-size: 18px;
}
</style>
