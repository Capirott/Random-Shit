from django.shortcuts import get_object_or_404, render
from django.http import HttpResponseRedirect
from django.urls import reverse
from django.views import generic
from django.contrib import messages

from .models import School, Student

class IndexView(generic.TemplateView):
    template_name = 'lgtrp/index.html'

    def get_context_data(self, **kwargs):
        context = super(IndexView, self).get_context_data(**kwargs)
        messages.info(self.request, 'Welcome stranger!')
        return context
        
class StudentInfoView(generic.DetailView):
    model = Student
    template_name = 'lgtrp/student_info.html'

class SchoolInfoView(generic.DetailView):
    model = School
    template_name = 'lgtrp/school_info.html'

class StudentView(generic.ListView):
	context_object_name = 'student_list'
	template_name = 'lgtrp/student.html'

	def get_queryset(self):
        	return School.objects.order_by('-name')

class SchoolView(generic.ListView):
	model = School
	context_object_name = 'school_list'
	template_name = 'lgtrp/school.html'
	def get_queryset(self):
		return School.objects.order_by('-name')


class StudentCreateView(generic.CreateView):
	model = Student
	fields = ['name']

