from django.contrib import admin
from .models import School, Student

class StudentAdmin(admin.ModelAdmin):
    fieldsets = [
            (None, {'fields': ['name']}),
            ('Registration Date', {'fields': ['registration_date']}),
    ]


admin.site.register(Student, StudentAdmin)

class StudentInline(admin.StackedInline):
    model = Student
    extra = 1

class SchoolAdmin(admin.ModelAdmin):
    fieldsets = [
        ('School Information', {'fields': ['name']})
    ]

#admin.site.register(School)
admin.site.register(School, SchoolAdmin)
