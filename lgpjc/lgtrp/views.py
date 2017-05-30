from django.shortcuts import get_object_or_404, render
from django.http import HttpResponseRedirect
from django.urls import reverse
from django.views import generic

from .models import School, Student

class IndexView(generic.ListView):
    template_name = 'lgtrp/index.html'
    context_object_name = 'school_list'
    
    def get_queryset(self):
        return School.objects.order_by('-name')

class StudentView(generic.DetailView):
    model = Student
    template_name = 'lgtrp/student.html'

class SchoolView(generic.DetailView):
    model = School
    template_name = 'lgtrp/school.html'
